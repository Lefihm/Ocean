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

    /** @brief The status of a task in the scheduler. */
    enum class TaskStatus {
        /** @brief The task is pending execution. */
        PENDING,
        /** @brief The task has completed successfully. */
        SUCCESS,
        /** @brief The task has timed out. */
        TIMEOUT,
        /** @brief The task was skipped. */
        SKIPPED,
        /** @brief The task has failed. */
        FAILED,

    };  // TaskStatus

    /** @brief A task that can be scheduled for execution. */
    struct Task {
        /**
         * @brief The name of the task.
         * @details This is used for profiling and debugging purposes.
         *          It should be unique within a task packet.
         */
        String name;
        /** @brief The action to perform when the task is executed. */
        std::function<void()> action;

        /**
         * @brief The timeout for the task.
         * @details This is the maximum amount of time the task is allowed to run.
         *          If the task does not complete within this time, it will be marked as TIMEOUT.
         *          A value of 0.0f means the task has no timeout.
         */
        Timestep timeout;
        /** @brief The duration of the task took to complete. */
        Time duration;

        /**
         * @brief The status of the task.
         * @details This is used to track the execution state of the task.
         *          It is updated by the scheduler when the task is executed.
         */
        std::atomic<TaskStatus> status = TaskStatus::PENDING;

        /**
         * @brief Construct a new Task object.
         * 
         * @param name The name of the task.
         * @param action The action to perform when the task is executed.
         * @param timeout The timeout for the task, defaults to 0.0f (no timeout).
         */
        Task(const String& name, std::function<void()> action, Timestep timeout = 0.0f);

        Task() = delete;
        Task(const Task&) noexcept;
        Task(Task&& other) noexcept;
        Task& operator = (const Task& rhs);

    };  // Task

    /** @brief A packet of tasks to be executed. */
    struct TaskPacket {
        /**
         * @brief The name of the task packet.
         * @details This is used for profiling and debugging purposes.
         *          It should be unique within the scheduler.
         */
        String name;

        /**
         * @brief The directed graph of tasks to be executed.
         * @details The graph structure allows for dependencies between tasks, where a task can depend on
         *          the completion of other tasks before it can be executed.
         */
        DirectedGraph<Task> graph;

        /**
         * @brief Construct a new TaskPacket object.
         * 
         * @param g The directed graph of tasks to be executed.
         * @param packetName The name of the task packet, defaults to an empty string.
         */
        TaskPacket(const String& packetName, DirectedGraph<Task>&& g) :
            name(packetName),
            graph(std::move(g))
        { }

        TaskPacket() = delete;

    };  // TaskPacket

    /**
     * @todo Rework so that the scheduler service is cleaner and does not
     *       result in major memory leaks.
     */

    /**
     * @brief The Scheduler Service of Ocean, manages task scheduling and execution.
     */
    class SchedulerService : public RuntimeService<SchedulerService> {
    public:
        /** @brief The task profiler callback type. */
        using TaskProfiler = std::function<void(const String&, Time)>;
        /** @brief The stage profiler callback type. */
        using StageProfiler = std::function<void(const String&, Time, u16)>;

    public:
        SchedulerService();
        virtual ~SchedulerService() = default;

        /** @brief Initialize the scheduler service. */
        virtual void Init() override;
        /** @brief Shutdown the scheduler service. */
        virtual void Shutdown() override;

        AssignServiceName(SchedulerService);
        AssignServicePriority(ServicePriority::DONT_CARE);

        /**
         * @brief Submit a single task for execution.
         * 
         * @param task The task to submit.
         * 
         * @return std::future<void> A future that will be satisfied when the task is completed.
         */
        static std::future<void> Submit(Task&& task);
        /**
         * @brief Submit a task packet for execution.
         * 
         * @param packet The task packet to submit.
         * 
         * @return std::future<void> A future that will be satisfied when the task packet is completed.
         */
        static std::future<void> Submit(TaskPacket&& packet);

    private:
        friend class Scheduler;

    private:
        OC_NO_COPY(SchedulerService);

        /**
         * @brief Run a task packet, executing all tasks in the packet according to their dependencies.
         * 
         * @param packet The task packet to run.
         */
        void RunPacket(TaskPacket& packet);

    private:
        /** @brief The instance of the SchedulerService, ensures only one instance exists. */
        inline static SchedulerService* s_Instance = nullptr;

        /** @brief The thread pool used for executing tasks. */
        ThreadPool m_Pool;

        /** @brief The task profiler callback, used to profile task execution times. */
        TaskProfiler m_TaskProfiler;
        /** @brief The stage profiler callback, used to profile task stage times. */
        StageProfiler m_StageProfiler;

    };    // SchedulerService

}   // Ocean
