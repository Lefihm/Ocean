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
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Platform/Events/Event.hpp"

#include "Ocean/Platform/Events/MouseCodes.hpp"

namespace Ocean {

    class MousePressedEvent : public Event {
    public:
        MousePressedEvent(cstring parentWindow, MouseCode code, b8 repeating = false) :
            Event(parentWindow),
            m_Code(code),
            m_IsRepeating(repeating)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE_BUTTON);
        AssignEventType(EventType::MOUSE_PRESSED);

        MouseCode GetButton() const { return this->m_Code; }
        b8 IsRepeating() const { return this->m_IsRepeating; }

    private:
        MouseCode m_Code;
        b8 m_IsRepeating;

    };  // MousePressedEvent

    class MouseReleasedEvent : public  Event {
    public:
        MouseReleasedEvent(cstring parentWindow, MouseCode code) :
            Event(parentWindow),
            m_Code(code)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE_BUTTON);
        AssignEventType(EventType::MOUSE_RELEASED);

        MouseCode GetButton() const { return this->m_Code; }

    private:
        MouseCode m_Code;

    };  // MouseReleaseEvent

    class MouseMoveEvent : public Event {
    public:
        MouseMoveEvent(cstring parentWindow, f32 x, f32 y) :
            Event(parentWindow),
            m_X(x),
            m_Y(y)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE);
        AssignEventType(EventType::MOUSE_MOVED);

        f32 GetXPos() const { return this->m_X; }
        f32 GetYPos() const { return this->m_Y; }

    private:
        f32 m_X;
        f32 m_Y;

    };  // MouseMoveEvent

    class MouseScrollEvent : public Event {
    public:
        MouseScrollEvent(cstring parentWindow, f32 xOffset, f32 yOffset) :
            Event(parentWindow),
            m_XOffset(xOffset),
            m_YOffset(yOffset)
        { }

        AssignEventCategory(EventCategoryFlags::MOUSE);
        AssignEventType(EventType::MOUSE_SCROLLED);

        f32 GetXOffset() const { return this->m_XOffset; }
        f32 GetYOffset() const { return this->m_YOffset; }

    private:
        f32 m_XOffset;
        f32 m_YOffset;

    };  // MouseScrollEvent

}   // Ocean
