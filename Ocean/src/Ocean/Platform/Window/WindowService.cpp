#include "WindowService.hpp"

#include "Ocean/Types/FloatingPoints.hpp"
#include "Ocean/Types/SmartPtrs.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Logger.hpp"

#include "Ocean/Platform/Window/WindowContext.hpp"

#include "Ocean/Platform/Events/EventService.hpp"
#include "Ocean/Platform/Events/WindowEvent.hpp"

// std
#include <utility>

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

    }

    /**
     * @brief A callback for GLFW to call when a Window receives a Unicode text input.
     * 
     * @note The Unicode characters do not map 1 to 1 to physical keys.
     * 
     * @param window The window ptr that received a Unicode input.
     * @param codepoint The Unicode code point of the character.
     */
    static void KeyboardCharCallback(GLFWwindow* window, u32 codepoint) {

    }

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

    }

    /**
     * @brief 
     * 
     * @param window 
     * @param xpos 
     * @param ypos 
     */
    static void MousePositionCallback(GLFWwindow* window, f64 xpos, f64 ypos) {

    }

    /**
     * @brief 
     * 
     * @param window 
     * @param xoffset 
     * @param yoffset 
     */
    static void MouseScrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset) {

    }

    // Window Callbacks

    /**
     * @brief A callback for GLFW to call when a Window requests to close.
     * 
     * @param window The window ptr that requested to close.
     */
    static void WindowCloseCallback(GLFWwindow* window) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        WindowCloseEvent e(ref->GetWindowName());
        SendEvent(e);
    }

    /**
     * @brief A callback for GLFW to call when a Window should refresh.
     * 
     * @note This is often called when the platform flattens windows
     *          and needs new screen data when the window is uncovered.
     * 
     * @param window The window ptr that should be refreshed.
     */
    static void WindowRefreshCallback(GLFWwindow* window) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        
    }

    /**
     * @brief A callback for GLFW to call when a Window changes in focus.
     * 
     * @param window The window ptr that has changed focus.
     * @param focused Records if the window has been focused or not. GLFW_TRUE if yes, GLFW_FALSE if no.
     */
    static void WindowFocusCallback(GLFWwindow* window, i32 focused) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));

        WindowFocusedEvent e(ref->GetWindowName());
        SendEvent(e);
    }

    /**
     * @brief A callback for GLFW to call when a Window is maximized or restored.
     * 
     * @param window The window prt that was maximized or restored.
     * @param maximized Records if the window has been maximized or not. GLFW_TRUE if yes, GLFW_FALSE if no.
     */
    static void WindowMaximizeCallback(GLFWwindow* window, i32 maximized) {
        const Window* ref = static_cast<Window*>(glfwGetWindowUserPointer(window));


    }

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

        WindowResizeEvent e(ref->GetWindowName(), width, height);
        SendEvent(e);
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
    }

    void WindowService::Shutdown() {
        if (!this->m_Windows.empty())
            this->m_Windows.erase(this->m_Windows.begin(), this->m_Windows.end());

        WindowContext::Shutdown();
    }

    void WindowService::PollEvents() {
        if (this->m_IsImmediate)
            glfwPollEvents();
        else
            glfwWaitEvents();
    }

    void WindowService::SwapBuffers() {
        /** @todo This is related to how Vulkan handles buffers separately to GLFW, will have to tell the RendererService to Swap Buffers instead. */
    }

    b8 WindowService::MakeWindow(u32 width, u32 height, cstring name) {
        this->m_Windows.try_emplace(name, MakeRef<Window>(width, height, name));

        GLFWwindow* ptr = this->m_Windows[name]->GetWindowPtr();

        glfwSetKeyCallback(ptr, KeyboardKeyCallback);
        glfwSetCharCallback(ptr, KeyboardCharCallback);

        glfwSetMouseButtonCallback(ptr, MouseButtonCallback);
        glfwSetCursorPosCallback(ptr, MousePositionCallback);
        glfwSetScrollCallback(ptr, MouseScrollCallback);

        glfwSetWindowCloseCallback(ptr, WindowCloseCallback);
        glfwSetWindowRefreshCallback(ptr, WindowRefreshCallback);
        glfwSetWindowFocusCallback(ptr, WindowFocusCallback);
        glfwSetWindowMaximizeCallback(ptr, WindowMaximizeCallback);
        glfwSetFramebufferSizeCallback(ptr, WindowResizeCallback);

        return true;
    }

    b8 WindowService::DestroyWindow(cstring name) {
        this->m_Windows.erase(name);

        return true;
    }

} // namespace Ocean
