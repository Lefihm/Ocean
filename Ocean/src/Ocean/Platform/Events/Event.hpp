/**
 * @file Event.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Macros.hpp"

namespace Ocean {

    /**
     * @brief 
     */
    typedef enum EventCategory : u8 {
        /** @brief Null default. */
        NONE = 0,

        APPLICATION    = 1 << 0,
        WINDOW         = 1 << 1,
        INPUT          = 1 << 2,
        KEYBOARD       = 1 << 3,
        MOUSE          = 1 << 4,
        MOUSE_BUTTON   = 1 << 5,

    }   EventCategory;

    /**
     * @brief 
     */
    typedef enum class EventType {
        NONE = 0,

        APP_SHOULD_CLOSE,

        WINDOW_CLOSE,
        WINDOW_RESIZE,
        WINDOW_FOCUSED,
        WINDOW_LOST_FOCUS,

        KEY_PRESSED,
        KEY_RELEASED,
        KEY_TYPED,

        MOUSE_PRESSED,
        MOUSE_RELEASED,
        MOUSE_MOVED,
        MOUSE_SCROLLED,

    }   EventType;

    /**
     * @brief A base event.
     */
    class Event {
    public:
        virtual ~Event() = default;

        b8 Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual u8 GetCategoryFlags() const = 0;

        b8 IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }

    #ifdef OC_DEBUG

        virtual cstring GetEventName() const = 0;

    #endif

        #define AssignEventType(type)           virtual EventType GetEventType() const override { return type; } \
                                                virtual cstring GetEventName() const override { return OCEAN_MAKESTRING(type); }

        #define AssignEventCategory(category)   virtual u8 GetCategoryFlags() const override { return category; }

    };  // Event

}   // Ocean
