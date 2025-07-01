/**
 * @file Window.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Macros.hpp"

struct GLFWwindow;

namespace Ocean {

    /**
     * @brief A unique identifier for a window.
     * 
     * This is used to identify windows within the Ocean Engine.
     */
    using WindowID = u16;

    /**
     * @brief The Window class represents a window in the Ocean Engine.
     * 
     * It encapsulates the GLFW window and provides methods to interact with it.
     */
    class Window {
    public:
        /**
         * @brief A struct to hold data related to the window.
         * 
         * This includes a reference to the Window object, its name, width, and height.
         */
        struct WindowData {
            /** @brief A reference to the Window object. */
            Window* ref;

            /** @brief The name of the window. */
            String name;

            /** @brief The width of the window. */
            u32 width;
            /** @brief The height of the window. */
            u32 height;

        };  // WindowData

        public:
        /**
         * @brief Constructs a new Window object.
         * 
         * @param id The unique identifier for the window.
         * @param width The initial width of the window.
         * @param height The initial height of the window.
         * @param name The name of the window.
         */
        Window(WindowID id, u32 width, u32 height, const String& name);
        ~Window();

        /** @brief Returns a pointer to the GLFW window. */
        GLFWwindow* GetWindowPtr() const { return this->p_Window; }

        /** @brief Returns the name of the window as a cstring. */
        cstring GetWindowName() const { return this->m_Data.name.c_str(); }

        /** @brief Returns the width of the window. */
        u32 GetWindowWidth() const { return this->m_Data.width; }
        /** @brief Returns the height of the window. */
        u32 GetWindowHeight() const { return this->m_Data.height; }

        /** @brief Returns the unique identifier for the window. */
        WindowID GetWindowID() const { return this->m_ID; }

        /** @brief Returns true if the window can be closed, false otherwise. */
        b8 WindowCanClose() const { return this->m_CanClose; }

    private:
        OC_NO_COPY(Window);

    private:
        /** @brief A pointer to the GLFW window. */
        GLFWwindow* p_Window;

        /** @brief The stored window data. */
        WindowData m_Data;

        /** @brief The unique identifier for the window. */
        WindowID m_ID;
        /**
         * @brief Indicates whether the window can be closed.
         * @details This is used to prevent the window from being closed
         *          when the application is still running or when certain conditions
         *          are met.
         */
        b8 m_CanClose;

    };  // Window

}   // Ocean
