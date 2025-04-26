/**
 * @file WindowService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Bool.hpp"

#include "Ocean/Core/Service.hpp"

namespace Ocean {

    /**
     * @brief 
     */
    class WindowService : public RuntimeService<WindowService> {
    public:
        WindowService();
        virtual ~WindowService();

        AssignServiceName(WindowService);
        AssignServicePriority(ServicePriority::IMMEDIATE);

        /**
         * @brief 
         */
        virtual void Init() override;
        /**
         * @brief 
         */
        virtual void Shutdown() override;

        /**
         * @brief 
         */
        void PollEvents();

        /**
         * @brief Set the event polling emmediacy.
         * 
         * @param isImmediate True for immediate polling, False otherwise.
         */
        inline void SetImmediacy(b8 isImmediate) { this->m_IsImmediate = isImmediate; }

    private:
        /**
         * @brief Records if events should be polled immediately or if the thread should sleep until events occur.
         *
         * @details Default value is TRUE.
         */
        b8 m_IsImmediate;

    };  // WindowService

}   // Ocean
