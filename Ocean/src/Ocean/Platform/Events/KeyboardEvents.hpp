/**
 * @file KeyboardEvents.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Platform/Events/Event.hpp"

#include "Ocean/Platform/Events/KeyCodes.hpp"

namespace Ocean {

    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(WindowID id, KeyCode key, b8 repeating = false) :
            Event(id),
            Key(key),
            IsRepeating(repeating)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_PRESSED);

        KeyCode Key;
        b8 IsRepeating;

    };  // KeyPressedEvent

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(WindowID id, KeyCode key) :
            Event(id),
            Key(key)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_RELEASED);

        KeyCode Key;

    };  // KeyReleasedEvent

    class KeyTypedEvent : public Event {
    public:
        KeyTypedEvent(WindowID id) :
            Event(id)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_TYPED);

    };  // KeyTypedEvent

}   // Ocean
