/**
 * @file Scheduler.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Service/SchedulerService.hpp"

namespace Ocean {

    class Scheduler {
    public:
        inline static std::future<void> SubmitTask(Task&& task) { return SchedulerService::s_Instance->Submit(std::move(task)); }

        inline static std::future<void> SubmitPacket(TaskPacket&& packet) { return SchedulerService::s_Instance->Submit(std::move(packet)); }

        // Begin Snapshot
        // End Snapshot

    };  // Scheduler

}   // Ocean
