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

    /** @brief An event representing a window close. */
    class WindowCloseEvent : public Event {
    public:
        /**
         * @brief Construct a new WindowCloseEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         */
        WindowCloseEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_CLOSE);

    };  // WindowCloseEvent

    /** @brief An event representing a window resize. */
    class WindowResizeEvent : public Event {
    public:
        /**
         * @brief Construct a new WindowResizeEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         * @param width The new width of the window.
         * @param height The new height of the window.
         */
        WindowResizeEvent(WindowID id, u32 width, u32 height) :
            Event(id),
            m_Width(width),
            m_Height(height)
        { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_RESIZE);

        /**
         * @brief Get the new width of the window.
         * 
         * @return u32 The new width.
         */
        u32 GetWidth() const { return this->m_Width; }
        /**
         * @brief Get the new height of the window.
         * 
         * @return u32 The new height.
         */
        u32 GetHeight() const { return this->m_Height; }

    private:
        /** @brief The new width of the window. */
        const u32 m_Width;
        /** @brief The new height of the window. */
        const u32 m_Height;

    };  // WindowResizeEvent

    /** @brief An event representing a window refresh. */
    class WindowRefreshEvent : public Event {
    public:
        /**
         * @brief Construct a new WindowRefreshEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         */
        WindowRefreshEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_REFRESH);

    };  // WindowRefreshEvent

    /** @brief An event representing a window focus. */
    class WindowFocusedEvent : public Event {
    public:
        /**
         * @brief Construct a new WindowFocusedEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         */
        WindowFocusedEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_FOCUSED);

    };  // WindowFocusedEvent

    /** @brief An event representing a window lost focus. */
    class WindowLostFocusEvent : public Event {
    public:
        /**
         * @brief Construct a new WindowLostFocusEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         */
        WindowLostFocusEvent(WindowID id) : Event(id) { }

        AssignEventCategory(EventCategoryFlags::WINDOW);
        AssignEventType(EventType::WINDOW_LOST_FOCUS);

    };  // WindowLostFocusEvent

}   // Ocean
