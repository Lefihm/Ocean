/**
 * @file Window.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {

    class Window {
    public:
        Window();
        ~Window();

    private:
        GLFWwindow* p_Window;

    };  // Window

}   // Ocean
