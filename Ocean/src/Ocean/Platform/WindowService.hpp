/**
 * @file WindowService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Service.hpp"

namespace Ocean {

    class WindowService : public RuntimeService<WindowService> {
    public:
        WindowService();
        virtual ~WindowService();

        AssignServiceName(WindowService);

        virtual void Init() override;
        virtual void Shutdown() override;

    };  // WindowService

}   // Ocean
