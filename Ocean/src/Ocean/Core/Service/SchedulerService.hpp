/**
 * @file SchedulerService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Exceptions.hpp"
#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Core/Service.hpp"

#include "Ocean/Primitives/DirectedGraph.hpp"
#include "Ocean/Primitives/DynamicArray.hpp"
#include "Ocean/Primitives/HashMap.hpp"
#include "Ocean/Primitives/ThreadPool.hpp"
#include "Ocean/Primitives/Time.hpp"
#include "Ocean/Types/Timestep.hpp"

// std
#include <atomic>
#include <condition_variable>
#include <exception>
#include <future>
#include <mutex>

namespace Ocean {

    enum class TaskStatus {
        PENDING,
        SUCCESS,
        TIMEOUT,
        SKIPPED,
        FAILED,

    };  // TaskStatus

    struct Task {
        String name;
        std::function<void()> action;

        Timestep timeout = 0.0f;
        Time duration = 0;

        std::atomic<TaskStatus> status = TaskStatus::PENDING;

        Task() = default;
        Task(const Task&) = delete;
        Task(Task&& other) noexcept :
            name(std::move(other.name)),
            action(std::move(other.action)),
            timeout(other.timeout),
            duration(other.duration),
            status(other.status.load())
        { }
        Task& operator = (const Task& rhs) {
            if (this != &rhs) {
                name = std::move(rhs.name);
                action = std::move(rhs.action);
                timeout = rhs.timeout;
                duration = rhs.duration;
                status.store(rhs.status.load());
            }

            return *this;
        }

    };  // Task

    struct TaskPacket {
        String name;

        DirectedGraph<Task> graph;

        TaskPacket(DirectedGraph<Task>&& g, String packetName = "") :
            name(std::move(packetName)),
            graph(std::move(g))
        { }

    };  // TaskPacket

    /**
     * @brief The Logging Service of Ocean, prints to a console.
     */
    class SchedulerService : public StaticService<SchedulerService> {
    public:
        using TaskProfiler = std::function<void(const String&, Time)>;
        using StageProfiler = std::function<void(const String&, Time, u16)>;

    public:
        SchedulerService();
        virtual ~SchedulerService();

        void Init() override;
        void Shutdown() override;

        AssignServiceName(SchedulerService);
        AssignServicePriority(ServicePriority::INITIAL);

        std::future<void> Submit(TaskPacket&& packet) {
            Ref<std::promise<void>> promise = MakeRef<std::promise<void>>();
            std::future<void> future = promise->get_future();

            this->m_Pool.Enqueue([this, p = std::move(promise), packet = std::move(packet)]() mutable {
                try {
                    RunPacket(packet);

                    p->set_value();
                }
                catch (...) {
                    p->set_exception(std::current_exception());
                }
            });

            return future;
        }

    private:
        void RunPacket(TaskPacket& packet) {
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

    private:
        ThreadPool m_Pool;

        TaskProfiler m_TaskProfiler;
        StageProfiler m_StageProfiler;

    };    // SchedulerService

}   // Ocean
