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

    /** @brief An event representing a key press. */
    class KeyPressedEvent : public Event {
    public:
        /**
         * @brief Constructs a new KeyPressedEvent object.
         * 
         * @param id The ID of the window that received the event.
         * @param key The key code of the pressed key.
         * @param repeating Whether the key is being held down (repeating) or not.
         */
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

    /** @brief An event representing a key release. */
    class KeyReleasedEvent : public Event {
    public:
        /**
         * @brief Constructs a new KeyReleasedEvent object.
         * 
         * @param id The ID of the window that received the event.
         * @param key The key code of the released key.
         */
        KeyReleasedEvent(WindowID id, KeyCode key) :
            Event(id),
            Key(key)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_RELEASED);

        KeyCode Key;

    };  // KeyReleasedEvent

    /** @brief An event representing a key being typed. */
    class KeyTypedEvent : public Event {
    public:
        /**
         * @brief Constructs a new KeyTypedEvent object.
         * 
         * @param id The ID of the window that received the event.
         */
        KeyTypedEvent(WindowID id) :
            Event(id)
        { }

        AssignEventCategory(EventCategoryFlags::KEYBOARD);
        AssignEventType(EventType::KEY_TYPED);

    };  // KeyTypedEvent

}   // Ocean
