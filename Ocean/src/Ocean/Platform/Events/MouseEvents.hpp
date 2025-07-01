/**
 * @file MouseEvents.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/FloatingPoints.hpp"

#include "Ocean/Platform/Events/Event.hpp"

#include "Ocean/Platform/Events/MouseCodes.hpp"

namespace Ocean {

    /** @brief An event representing a mouse button press. */
    class MousePressedEvent : public Event {
    public:
        /**
         * @brief Construct a new MousePressedEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         * @param code The MouseCode of the button pressed.
         * @param repeating Whether the button is being held down (repeating) or not.
         */
        MousePressedEvent(WindowID id, MouseCode code, b8 repeating = false) :
            Event(id),
            Button(code),
            IsRepeating(repeating)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE_BUTTON);
        AssignEventType(EventType::MOUSE_PRESSED);

        MouseCode Button;
        b8 IsRepeating;

    };  // MousePressedEvent

    /** @brief An event representing a mouse button release. */
    class MouseReleasedEvent : public  Event {
    public:
        /**
         * @brief Construct a new MouseReleasedEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         * @param code The MouseCode of the button released.
         */
        MouseReleasedEvent(WindowID id, MouseCode code) :
            Event(id),
            Button(code)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE_BUTTON);
        AssignEventType(EventType::MOUSE_RELEASED);

        MouseCode Button;

    };  // MouseReleaseEvent

    /** @brief An event representing a mouse move. */
    class MouseMoveEvent : public Event {
    public:
        /**
         * @brief Construct a new MouseMoveEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         * @param x The x position of the mouse.
         * @param y The y position of the mouse.
         */
        MouseMoveEvent(WindowID id, f32 x, f32 y) :
            Event(id),
            xPos(x),
            yPos(y)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE);
        AssignEventType(EventType::MOUSE_MOVED);

        f32 xPos;
        f32 yPos;

    };  // MouseMoveEvent

    /** @brief An event representing a mouse scroll. */
    class MouseScrollEvent : public Event {
    public:
        /**
         * @brief Construct a new MouseScrollEvent object.
         * 
         * @param id The WindowID of the window that received the event.
         * @param xOffset The x offset of the scroll.
         * @param yOffset The y offset of the scroll.
         */
        MouseScrollEvent(WindowID id, f32 xOffset, f32 yOffset) :
            Event(id),
            xOffset(xOffset),
            yOffset(yOffset)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE);
        AssignEventType(EventType::MOUSE_SCROLLED);

        f32 xOffset;
        f32 yOffset;

    };  // MouseScrollEvent

}   // Ocean
