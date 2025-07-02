/**
 * @file Event.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Core/Logger.hpp"
#include "Ocean/Types/Bool.hpp"
#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Macros.hpp"

namespace Ocean {

    using WindowID = u16;

    /**
     * @brief An enum of different events that can occur.
     */
    typedef enum class EventCategory : u8 {
        APPLICATION    = 0,
        WINDOW         = 1,
        INPUT          = 2,
        KEYBOARD       = 3,
        MOUSE          = 4,
        MOUSE_BUTTON   = 5,

        EVENT_CATEGORY_MAX

    }   EventCategory;

    /**
     * @brief An enum of EventCategory's as bit-flags.
     */
    typedef enum EventCategoryFlags : u8 {
        /** @brief Null default. */
        NONE           = 0,

        APPLICATION    = 1 << 0,
        WINDOW         = 1 << 1,
        INPUT          = 1 << 2,
        KEYBOARD       = 1 << 3,
        MOUSE          = 1 << 4,
        MOUSE_BUTTON   = 1 << 5,

    } EventCategoryFlags;

    /**
     * @brief An enum of different types of events.
     */
    typedef enum class EventType : u8 {
        /** @brief Null default. */
        NONE = 0,

        APP_SHOULD_CLOSE,

        WINDOW_CLOSE,
        WINDOW_RESIZE,
        WINDOW_REFRESH,
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
        Event(WindowID parentId = 0) :
            ParentID(parentId)
        { }
        Event(const Event &) = default;
        Event(Event &&) = delete;
        virtual ~Event() = default;

        Event &operator=(const Event &) = default;
        Event &operator=(Event &&) = delete;

        b8 operator == (const Event& rhs) const {
            return this->ParentID == rhs.ParentID && this->GetCategoryFlags() == rhs.GetCategoryFlags() && this->GetEventType() == rhs.GetEventType();
        }
        b8 operator != (const Event& rhs) const {
            return !(*this == rhs);
        }

        b8 Handled = false;
        WindowID ParentID;

        virtual EventType GetEventType() const = 0;
        virtual u8 GetCategoryFlags() const = 0;

        b8 IsInCategory(EventCategoryFlags category) const { return GetCategoryFlags() & category; }

    // #ifdef OC_DEBUG

        virtual cstring GetEventName() const { return "Base Event"; }

    // #endif

        #define AssignEventType(type)           static EventType GetStaticType() { return type; } \
                                                virtual EventType GetEventType() const override { return GetStaticType(); } \
                                                virtual cstring GetEventName() const override { return OCEAN_MAKESTRING(type); }

        #define AssignEventCategory(category)   virtual u8 GetCategoryFlags() const override { return category; }

    };  // Event

    class AppShouldCloseEvent : public Event {
    public:
        AssignEventCategory(EventCategoryFlags::APPLICATION);
        AssignEventType(EventType::APP_SHOULD_CLOSE);

    };  // AppShouldCloseEvent

}   // Ocean
