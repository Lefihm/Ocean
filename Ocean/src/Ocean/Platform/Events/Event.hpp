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

namespace Ocean {

    /**
     * @brief An enum to represent the level of an event.
     */
    typedef enum EventLevel {
        /** @brief Null default. */
        NONE = 0,

        /** @brief System / Window event level. */
        SYSTEM,
        /** @brief Internal application event level. */
        APPLICATION,
        /** @brief User input event level. */
        USER

    }   EventLevel;

    /**
     * @brief A base event that stores the event level.
     */
    class Event {
    public:
        Event(EventLevel level);
        virtual ~Event();

        /**
         * @brief Get the EventLevel of the Event.
         * 
         * @return EventLevel 
         */
        inline EventLevel GetEventLevel() const { return this->m_Level; }

        /**
         * @brief Returns if the Event is handled.
         * 
         * @return b8
         */
        inline b8 IsHandled() const { return this->m_IsHandled; }
        /**
         * @brief Set the Event as handled.
         */
        inline void SetAsHandled() { this->m_IsHandled = true; }

    private:
        /** @brief Stores the EventLevel of the Event. */
        const EventLevel m_Level;

        /** @brief Records if the Event is handled or not. */
        b8 m_IsHandled;

    };  // Event



    class SystemEvent : public Event {
    public:
        SystemEvent(EventLevel level);
        virtual ~SystemEvent();

    };  // SystemEvent



    class ApplicationEvent : public Event {
    public:
        ApplicationEvent(EventLevel level);
        virtual ~ApplicationEvent();

    };  // ApplicationEvent



    class UserEvent : public Event {
    public:
        UserEvent(EventLevel level);
        virtual ~UserEvent();

    };  // ApplicationEvent

}   // Ocean
