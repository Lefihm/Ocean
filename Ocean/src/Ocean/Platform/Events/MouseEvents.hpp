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

    class MousePressedEvent : public Event {
    public:
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

    class MouseReleasedEvent : public  Event {
    public:
        MouseReleasedEvent(WindowID id, MouseCode code) :
            Event(id),
            Button(code)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE_BUTTON);
        AssignEventType(EventType::MOUSE_RELEASED);

        MouseCode Button;

    };  // MouseReleaseEvent

    class MouseMoveEvent : public Event {
    public:
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

    class MouseScrollEvent : public Event {
    public:
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
