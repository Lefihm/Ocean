/**
 * @file WindowEvent.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Macros.hpp"

#include "Ocean/Platform/Events/Event.hpp"

namespace Ocean {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent(cstring windowName) :
            m_Window(windowName)
        { }

        AssignEventCategory(EventCategory::WINDOW | EventCategory::APPLICATION);
        AssignEventType(EventType::WINDOW_CLOSE);

        cstring GetParentName() const { return this->m_Window; }

    private:
        OC_NO_COPY(WindowCloseEvent);

    private:
        const cstring m_Window;

    };  // WindowCloseEvent

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(cstring windowName, u32 width, u32 height) :
            m_Window(windowName),
            m_Width(width),
            m_Height(height)
        { }

        AssignEventCategory(EventCategory::WINDOW);
        AssignEventType(EventType::WINDOW_RESIZE);

        u32 GetWidth() const { return this->m_Width; }
        u32 GetHeight() const { return this->m_Height; }

        cstring GetParentName() const { return this->m_Window; }

    private:
        OC_NO_COPY(WindowResizeEvent);

    private:
        const cstring m_Window;

        const u32 m_Width;
        const u32 m_Height;

    };  // WindowResizeEvent

    class WindowFocusedEvent : public Event {
    public:
        WindowFocusedEvent(cstring windowName) :
            m_Window(windowName)
        { }

        AssignEventCategory(EventCategory::WINDOW);
        AssignEventType(EventType::WINDOW_FOCUSED);

        cstring GetParentName() const { return this->m_Window; }

    private:
        OC_NO_COPY(WindowFocusedEvent);

    private:
        const cstring m_Window;

    };  // WindowFocusedEvent

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent(cstring windowName) :
            m_Window(windowName)
        { }

        AssignEventCategory(EventCategory::WINDOW);
        AssignEventType(EventType::WINDOW_LOST_FOCUS);

        cstring GetParentName() const { return this->m_Window; }

    private:
        OC_NO_COPY(WindowLostFocusEvent);

    private:
        const cstring m_Window;

    };  // WindowLostFocusEvent

}   // Ocean
