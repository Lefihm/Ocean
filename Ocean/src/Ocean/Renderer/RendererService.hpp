/**
 * @file RendererService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Service.hpp"

namespace Ocean {

    class RendererService : public RuntimeService<RendererService> {
    public:
        RendererService();
        virtual ~RendererService();

        AssignServiceName(RendererService);
        AssignServicePriority(ServicePriority::DONT_CARE);

        virtual void Init() override;
        virtual void Shutdown() override;

    private:
        inline static RendererService* s_Instance = nullptr;

    };  // RendererService

}   // Ocean
