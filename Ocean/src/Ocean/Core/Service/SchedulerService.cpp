#include "SchedulerService.hpp"

#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Core/Exceptions.hpp"

#include "Ocean/Primitives/DirectedGraph.hpp"
#include "Ocean/Primitives/HashMap.hpp"
#include "Ocean/Primitives/Time.hpp"

// std
#include <exception>
#include <future>

namespace Ocean {

    Task::Task(const Task& rhs) noexcept
        : name(rhs.name),
          action(rhs.action),
          timeout(rhs.timeout),
          duration(rhs.duration),
          status(rhs.status.load())
    { }

    Task::Task(Task&& other) noexcept :
        name(std::move(other.name)),
        action(std::move(other.action)),
        timeout(other.timeout),
        duration(other.duration),
        status(other.status.load())
    { }

    Task& Task::operator = (const Task& rhs) {
        if (this != &rhs) {
            name = std::move(rhs.name);
            action = std::move(rhs.action);
            timeout = rhs.timeout;
            duration = rhs.duration;
            status.store(rhs.status.load());
        }

        return *this;
    }



    SchedulerService::SchedulerService() :
        StaticService(),
        m_Pool(),
        m_TaskProfiler(nullptr),
        m_StageProfiler(nullptr)
    {
        if (!s_Instance)
            s_Instance = this;
    }

    void SchedulerService::Init() { }

    void SchedulerService::Shutdown() { }

    std::future<void> SchedulerService::Submit(TaskPacket&& packet) {
        Ref<std::promise<void>> promise = MakeRef<std::promise<void>>();
        std::future<void> future = promise->get_future();

        s_Instance->m_Pool.Enqueue([p = std::move(promise), packet = std::move(packet)]() mutable {
            try {
                s_Instance->RunPacket(packet);

                p->set_value();
            }
            catch (...) {
                p->set_exception(std::current_exception());
            }
        });

        return future;
    }

    std::future<void> SchedulerService::Submit(Task&& task) {
        TaskPacket packet;
        packet.name = task.name;

        DirectedGraph<Task>& graph = packet.graph;
        graph.AddNode(std::move(task));

        return Submit(std::move(packet));
    }

    void SchedulerService::RunPacket(TaskPacket& packet) {
        DirectedGraph<Task>& graph = packet.graph;
        DynamicArray<DirectedGraph<Task>::Node>& nodes = graph.GetNodes();
        auto stages = graph.GetParallelPaths();

        UnorderedMap<DirectedGraph<Task>::NodeID, std::atomic<b8>> blocked;

        for (const DirectedGraph<Task>::Node& node : nodes)
            blocked[node.id] = false;

        std::mutex stageMutex;
        std::condition_variable stageDone;
        std::exception_ptr error = nullptr;

        for (u16 stageIndex = 0; stageIndex < stages.Size(); stageIndex++) {
            const DynamicArray<DirectedGraph<Task>::NodeID> stage = stages[stageIndex];
            std::atomic<u16> remaining = stage.Size();

            Time stageStart = oTimeNow();

            for (DirectedGraph<Task>::NodeID id : stage) {
                this->m_Pool.Enqueue([&, id]() {
                    auto& task = nodes[id].data;

                    if (blocked[id]) {
                        task.status = TaskStatus::SKIPPED;

                        if (--remaining == 0)
                            stageDone.notify_one();

                        return;
                    }

                    Time start = oTimeNow();

                    try {
                        std::packaged_task<void()> wrapped(task.action);
                        auto future = wrapped.get_future();
                        std::thread(std::move(wrapped)).detach();

                        if (task.timeout == 0.0f) {
                            future.wait();

                            task.status = TaskStatus::SUCCESS;
                        }
                        else if (future.wait_for(task.timeout.GetChronoMilliseconds()) == std::future_status::ready) {
                            future.get();

                            task.status = TaskStatus::SUCCESS;
                        }
                        else {
                            task.status = TaskStatus::TIMEOUT;

                            throw Exception(Error::RUNTIME_ERROR, ("Task [" + task.name + "] timed out.").c_str());
                        }
                    }
                    catch (...) {
                        task.status = TaskStatus::FAILED;

                        if (!error)
                            error = std::current_exception();
                    }

                    task.duration = oTimeFrom(start);

                    if (this->m_TaskProfiler)
                        this->m_TaskProfiler(task.name, task.duration);

                    if (task.status != TaskStatus::SUCCESS)
                        for (auto dependent : graph.GetOutEdges(id))
                            blocked[dependent] = true;

                    if (--remaining == 0)
                        stageDone.notify_one();
                });
            }

            std::unique_lock<std::mutex> lock(stageMutex);

            stageDone.wait(lock, [&] {
                return remaining == 0;
            });

            Time stageEnd = oTimeNow();

            if (this->m_StageProfiler)
                this->m_StageProfiler(packet.name, stageEnd - stageStart, stageIndex);

            if (error)
                std::rethrow_exception(error);
        }
    }

}   // Ocean
