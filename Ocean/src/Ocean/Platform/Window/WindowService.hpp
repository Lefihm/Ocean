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
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Primitives/HashMap.hpp"

#include "Ocean/Core/Service.hpp"

#include "Ocean/Platform/Window/Window.hpp"

namespace Ocean {

    /**
     * @brief A service to handle Windows.
     */
    class WindowService : public RuntimeService<WindowService> {
    public:
        WindowService();
        virtual ~WindowService();

        AssignServiceName(WindowService);
        AssignServicePriority(ServicePriority::IMMEDIATE);

        inline static WindowService* Instance() { return s_Instance; }

        /**
         * @brief Initializes the WindowService and any necessary platform interaction systems.
         */
        virtual void Init() override;
        /**
         * @brief Shuts down the WindowService and any attached platform systems. 
         */
        virtual void Shutdown() override;

        /**
         * @brief Polls the system for events. 
         */
        void PollEvents();

        /**
         * @brief Swaps the buffers of each Window.
         */
        void SwapBuffers();

        /**
         * @brief Set the event polling emmediacy.
         * 
         * @param isImmediate True for immediate polling, False otherwise.
         */
        inline void SetImmediacy(b8 isImmediate) { this->m_IsImmediate = isImmediate; }

        /** @todo WindowConfig for extra settings. */
        /**
         * @brief Makes a Window for the application.
         * 
         * @param x The width of the Window.
         * @param y The height of the Window.
         * @param name The name of the Window.
         * @return b8 True if successful, False otherwise.
         */
        b8 MakeWindow(u32 width, u32 height, cstring name);
        b8 DestroyWindow(cstring name);

    private:
        inline static WindowService* s_Instance = nullptr;

        /**
         * @brief Records if events should be polled immediately or if the thread should sleep until events occur.
         *
         * @details Default value is TRUE.
         */
        b8 m_IsImmediate;

        /** @brief The list of Windows that exist. */
        UnorderedMap<cstring, Ref<Window>> m_Windows;

    };  // WindowService

}   // Ocean
