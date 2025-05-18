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

    class Window {
    public:
        Window(u32 width, u32 height, const String& name);
        ~Window();

        GLFWwindow* GetWindowPtr() const { return this->p_Window; }

        cstring GetWindowName() const { return this->m_Data.name.c_str(); }

        u32 GetWindowWidth() const { return this->m_Data.width; }
        u32 GetWindowHeight() const { return this->m_Data.height; }

        b8 WindowCanClose() const { return this->m_CanClose; }

    private:
        struct WindowData {
            Window* ref;

            String name;

            u32 width;
            u32 height;

        };  // WindowData

    private:
        OC_NO_COPY(Window);

    private:
        GLFWwindow* p_Window;

        WindowData m_Data;

        b8 m_CanClose;

    };  // Window

}   // Ocean
