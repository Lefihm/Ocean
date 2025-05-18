#include "WindowService.hpp"

#include "Ocean/Platform/Events/Event.hpp"
#include "Ocean/Types/FloatingPoints.hpp"
#include "Ocean/Types/SmartPtrs.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Logger.hpp"

#include "Ocean/Platform/Window/WindowContext.hpp"

#include "Ocean/Platform/Events/EventService.hpp"
#include "Ocean/Platform/Events/EventDispatcher.hpp"

#include "Ocean/Platform/Events/WindowEvents.hpp"
#include "Ocean/Platform/Events/KeyboardEvents.hpp"
#include "Ocean/Platform/Events/MouseEvents.hpp"

// libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {


    // Keyboard Callbacks

    /**
     * @brief A callback for GLFW to call when a Window receives a key press,
     *        repeated, or release action.
     * 
     * @note The key callback receives actions for the physical keys, not typed characters.
     * 
     * @param window The window ptr that received an action.
     * @param key The keyboard key that was pressed or released.
     * @param scancode The platform-specific scancode of the key.
     * @param action GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT.
     * @param mods A bit field describing which modifier keys were held.
     */
    static void KeyboardKeyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (action == GLFW_PRESS)
            EventService::SignalEvent(MakeScope<KeyPressedEvent>(ref->GetWindowName(), key));
        else if (action == GLFW_REPEAT)
            EventService::SignalEvent(MakeScope<KeyPressedEvent>(ref->GetWindowName(), key, true));
        else
            EventService::SignalEvent(MakeScope<KeyReleasedEvent>(ref->GetWindowName(), key));
    }

    /**
     * @brief A callback for GLFW to call when a Window receives a Unicode text input.
     * 
     * @note The Unicode characters do not map 1 to 1 to physical keys.
     * 
     * @param window The window ptr that received a Unicode input.
     * @param codepoint The Unicode code point of the character.
     */
    // static void KeyboardCharCallback(GLFWwindow* window, u32 codepoint) {

    // }

    // Mouse Callbacks

    /**
     * @brief 
     * 
     * @param window 
     * @param button 
     * @param action 
     * @param mods 
     */
    static void MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (action == GLFW_PRESS)
            EventService::SignalEvent(MakeScope<MousePressedEvent>(ref->GetWindowName(), button));
        else if (action == GLFW_REPEAT)
            EventService::SignalEvent(MakeScope<MousePressedEvent>(ref->GetWindowName(), button, true));
        else
            EventService::SignalEvent(MakeScope<MouseReleasedEvent>(ref->GetWindowName(), button));
    }

    /**
     * @brief 
     * 
     * @param window 
     * @param xpos 
     * @param ypos 
     */
    static void MousePositionCallback(GLFWwindow* window, f64 xpos, f64 ypos) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        EventService::SignalEvent(MakeScope<MouseMoveEvent>(ref->GetWindowName(), xpos, ypos));
    }

    /**
     * @brief 
     * 
     * @param window 
     * @param xoffset 
     * @param yoffset 
     */
    static void MouseScrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        EventService::SignalEvent(MakeScope<MouseScrollEvent>(ref->GetWindowName(), xoffset, yoffset));
    }

    // Window Callbacks

    /**
     * @brief A callback for GLFW to call when a Window requests to close.
     * 
     * @param window The window ptr that requested to close.
     */
    static void WindowCloseCallback(GLFWwindow* window) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        EventService::SignalEvent(MakeScope<WindowCloseEvent>(ref->GetWindowName()));
    }

    /**
     * @brief A callback for GLFW to call when a Window should refresh.
     * 
     * @note This is often called when the platform flattens windows
     *       and needs new screen data when the window is uncovered.
     * 
     * @param window The window ptr that should be refreshed.
     */
    static void WindowRefreshCallback(GLFWwindow* window) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        EventService::SignalEvent(MakeScope<WindowRefreshEvent>(ref->GetWindowName()));
    }

    /**
     * @brief A callback for GLFW to call when a Window changes in focus.
     * 
     * @param window The window ptr that has changed focus.
     * @param focused Records if the window has been focused or not. GLFW_TRUE if yes, GLFW_FALSE if no.
     */
    static void WindowFocusCallback(GLFWwindow* window, i32 focused) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (focused == GLFW_TRUE)
            EventService::SignalEvent(MakeScope<WindowFocusedEvent>(ref->GetWindowName()));
        else
            EventService::SignalEvent(MakeScope<WindowLostFocusEvent>(ref->GetWindowName()));
    }

    /**
     * @brief A callback for GLFW to call when a Window is maximized or restored.
     * 
     * @param window The window prt that was maximized or restored.
     * @param maximized Records if the window has been maximized or not. GLFW_TRUE if yes, GLFW_FALSE if no.
     */
    /**
     * static void WindowMaximizeCallback(GLFWwindow* window, i32 maximized) {
     *     const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));
     * }
     */

    /**
     * @brief A callback for GLFW to call when a Window has been resized.
     * 
     * @note This callback should be used for glfwSetFramebufferSizeCallback,
     *       not glfwSetSizeCallback. This is because Ocean relies on framebuffer
     *       handling, and we do not care for screenspace coordinates yet.
     * 
     * @param window The window ptr that has been resized.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    static void WindowResizeCallback(GLFWwindow* window, i32 width, i32 height) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        EventService::SignalEvent(MakeScope<WindowResizeEvent>(ref->GetWindowName(), width, height));
    }



    WindowService::WindowService() :
        RuntimeService(),
        m_IsImmediate(true),
        m_Windows()
    {
        if (!this->s_Instance)
            this->s_Instance = this;
    }

    WindowService::~WindowService()
    {
        
    }

    void WindowService::Init() {
        WindowContext::Init();

        oprints("Window server is %s\n", WindowContext::GetPlatformName());

        EventService::AddEventCallback<EventCategory::WINDOW>(OC_BIND_EVENT_FN(WindowService::OnEvent));
    }

    void WindowService::Shutdown() {
        if (!this->m_Windows.empty())
            this->m_Windows.erase(this->m_Windows.begin(), this->m_Windows.end());

        WindowContext::Shutdown();
    }

    void WindowService::PollEvents() {
        if (s_Instance->m_IsImmediate)
            glfwPollEvents();
        else
            glfwWaitEvents();
    }

    void WindowService::SwapBuffers() {
        /** @todo This is related to how Vulkan handles buffers separately to GLFW, will have to tell the RendererService to Swap Buffers instead. */
    }

    void WindowService::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(OC_BIND_EVENT_FN(WindowService::WindowClosed));
    }

    b8 WindowService::MakeWindow(u32 width, u32 height, cstring name) {
        s_Instance->m_Windows.try_emplace(name, MakeScope<Window>(width, height, name));

        oprints("Creating Window: %s\n", s_Instance->m_Windows[name]->GetWindowName());

        GLFWwindow* ptr = s_Instance->m_Windows[name]->GetWindowPtr();

        glfwSetKeyCallback(ptr, KeyboardKeyCallback);
        // glfwSetCharCallback(ptr, KeyboardCharCallback);

        glfwSetMouseButtonCallback(ptr, MouseButtonCallback);
        glfwSetCursorPosCallback(ptr, MousePositionCallback);
        glfwSetScrollCallback(ptr, MouseScrollCallback);

        glfwSetWindowCloseCallback(ptr, WindowCloseCallback);
        glfwSetWindowRefreshCallback(ptr, WindowRefreshCallback);
        glfwSetWindowFocusCallback(ptr, WindowFocusCallback);
        // glfwSetWindowMaximizeCallback(ptr, WindowMaximizeCallback);
        glfwSetFramebufferSizeCallback(ptr, WindowResizeCallback);

        return true;
    }

    b8 WindowService::DestroyWindow(cstring name) {
        if (s_Instance->m_Windows[name]->WindowCanClose()) {
            s_Instance->m_Windows.erase(name);

            return true;
        }

        return false;
    }

    b8 WindowService::WindowClosed(WindowCloseEvent& e) {
        if (this->m_Windows[e.GetParentWindow()]->WindowCanClose())
            DestroyWindow(e.GetParentWindow());
        else
            return false;

        if (this->m_Windows.empty())
            EventService::SignalEvent(MakeScope<AppShouldCloseEvent>());

        return true;
    }

}   // namespace Ocean
