#include "Window.hpp"

#include "Ocean/Core/Exceptions.hpp"

// libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {

    Window::Window(u32 width, u32 height, const String& name) :
        p_Window(nullptr),
        m_Data { this, name, width, height },
        m_CanClose(true)
    {
        /** @todo Window relationship / config. */

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        this->p_Window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

        if (!this->p_Window)
            throw Exception(Error::BAD_WINDOW_CREATION, "Failed to create Window!");

        glfwSetWindowUserPointer(this->p_Window, &this->m_Data);

        /** @todo Configure GLFW context per RendererAPI. */
    }

    Window::~Window()
    {
        glfwDestroyWindow(this->p_Window);
    }

}   // Ocean
