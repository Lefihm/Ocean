/**
 * @file KeyboardEvents.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Strings.hpp"

#include "Ocean/Platform/Events/Event.hpp"

#include "Ocean/Platform/Events/KeyCodes.hpp"

namespace Ocean {

    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(cstring parentWindow, KeyCode key, b8 repeating = false) :
            Event(parentWindow),
            m_Key(key),
            m_Repeating(repeating)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_PRESSED);

        KeyCode GetKey() const { return this->m_Key; }
        b8 IsRepeating() const { return this->m_Repeating; }

    private:
        KeyCode m_Key;
        b8 m_Repeating;

    };  // KeyPressedEvent

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(cstring parentWindow, KeyCode key) :
            Event(parentWindow),
            m_Key(key)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_RELEASED);

        KeyCode GetKey() const { return this->m_Key; }

    private:
        KeyCode m_Key;

    };  // KeyReleasedEvent

    class KeyTypedEvent : public Event {
    public:
        KeyTypedEvent(cstring parentWindow) :
            Event(parentWindow)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_TYPED);

    private:


    };  // KeyTypedEvent

}   // Ocean
