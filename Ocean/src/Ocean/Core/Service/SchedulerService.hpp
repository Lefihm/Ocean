/**
 * @file SchedulerService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Timestep.hpp"

#include "Ocean/Core/Service.hpp"

#include "Ocean/Primitives/DirectedGraph.hpp"
#include "Ocean/Primitives/ThreadPool.hpp"
#include "Ocean/Primitives/Time.hpp"

// std
#include <atomic>
#include <future>

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
        Task(const Task&) noexcept;
        Task(Task&& other) noexcept;
        Task& operator = (const Task& rhs);

    };  // Task

    struct TaskPacket {
        String name;

        DirectedGraph<Task> graph;

        TaskPacket() = default;
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
        virtual ~SchedulerService() = default;

        virtual void Init() override;
        virtual void Shutdown() override;

        AssignServiceName(SchedulerService);
        AssignServicePriority(ServicePriority::INITIAL);

        static std::future<void> Submit(TaskPacket&& packet);
        static std::future<void> Submit(Task&& task);

    private:
        friend class Scheduler;

    private:
        void RunPacket(TaskPacket& packet);

    private:
        inline static SchedulerService* s_Instance = nullptr;

        ThreadPool m_Pool;

        TaskProfiler m_TaskProfiler;
        StageProfiler m_StageProfiler;

    };    // SchedulerService

}   // Ocean
