#include "WindowService.hpp"

#include "Ocean/Core/Logger.hpp"

#include "Ocean/Platform/WindowContext.hpp"

// libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {





    WindowService::WindowService() :
        RuntimeService(),
        m_IsImmediate(true)
    {
        
    }

    WindowService::~WindowService()
    {
        
    }

    void WindowService::Init() {
        WindowContext::Init();

        oprints("Window server is %s\n", WindowContext::GetPlatformName());
    }

    void WindowService::Shutdown() {
        WindowContext::Shutdown();
    }

    void WindowService::PollEvents() {
        if (this->m_IsImmediate)
            glfwPollEvents();
        else
            glfwWaitEvents();
    }

} // namespace Ocean
