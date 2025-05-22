/**
 * @file WindowEvents.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Platform/Events/Event.hpp"

namespace Ocean {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_CLOSE);

    };  // WindowCloseEvent

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(WindowID id, u32 width, u32 height) :
            Event(id),
            m_Width(width),
            m_Height(height)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_RESIZE);

        u32 GetWidth() const { return this->m_Width; }
        u32 GetHeight() const { return this->m_Height; }

    private:
        const u32 m_Width;
        const u32 m_Height;

    };  // WindowResizeEvent

    class WindowRefreshEvent : public Event {
    public:
        WindowRefreshEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_REFRESH);

    };  // WindowRefreshEvent

    class WindowFocusedEvent : public Event {
    public:
        WindowFocusedEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_FOCUSED);

    };  // WindowFocusedEvent

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_LOST_FOCUS);

    };  // WindowLostFocusEvent

}   // Ocean
