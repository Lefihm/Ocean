/**
 * @file SchedulerService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Service.hpp"

namespace Ocean {

    /**
     * @brief The Logging Service of Ocean, prints to a console.
     */
    class SchedulerService : public StaticService<SchedulerService> {
    public:
        SchedulerService();
        virtual ~SchedulerService();

        AssignServiceName(SchedulerService);
        AssignServicePriority(ServicePriority::INITIAL);

    };    // LogService

}   // Ocean
