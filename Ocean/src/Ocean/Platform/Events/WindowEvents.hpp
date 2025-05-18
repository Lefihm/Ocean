/**
 * @file WindowEvents.hpp
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
        WindowCloseEvent(cstring parentWindow) :
            Event(parentWindow)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW | EventCategoryFlags::APPLICATION);
        AssignEventType(EventType::WINDOW_CLOSE);

    private:
        OC_NO_COPY(WindowCloseEvent);

    };  // WindowCloseEvent

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(cstring parentWindow, u32 width, u32 height) :
            Event(parentWindow),
            m_Width(width),
            m_Height(height)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_RESIZE);

        u32 GetWidth() const { return this->m_Width; }
        u32 GetHeight() const { return this->m_Height; }

    private:
        OC_NO_COPY(WindowResizeEvent);

    private:
        const u32 m_Width;
        const u32 m_Height;

    };  // WindowResizeEvent

    class WindowRefreshEvent : public Event {
    public:
        WindowRefreshEvent(cstring parentWindow) :
            Event(parentWindow)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_REFRESH);

    };  // WindowRefreshEvent

    class WindowFocusedEvent : public Event {
    public:
        WindowFocusedEvent(cstring parentWindow) :
            Event(parentWindow)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_FOCUSED);

    private:
        OC_NO_COPY(WindowFocusedEvent);

    };  // WindowFocusedEvent

    class WindowLostFocusEvent : public Event {
    public:
        WindowLostFocusEvent(cstring parentWindow) :
            Event(parentWindow)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_LOST_FOCUS);

    private:
        OC_NO_COPY(WindowLostFocusEvent);

    };  // WindowLostFocusEvent

}   // Ocean
