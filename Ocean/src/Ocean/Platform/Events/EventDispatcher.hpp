#pragma once

#include "Ocean/Types/Bool.hpp"

#include "Event.hpp"

namespace Ocean {

    /**
     * @brief A class to dispatch events to specific event types.
     */
    class EventDispatcher {
    public:
        /**
         * @brief Construct a new EventDispatcher object.
         * 
         * @param event The Event to dispatch.
         */
        EventDispatcher(Event& event) :
            m_Event(event)
        { }

        /**
         * @brief Dispatches the event to the given function if the event type matches.
         * 
         * @tparam T The Event type to dispatch to.
         * @tparam F The function type to call if the event type matches.
         * 
         * @param func The function to call if the event type matches.
         * 
         * @return b8 True if the event was dispatched, false otherwise.
         */
        template <typename T, typename F>
        b8 Dispatch(const F& func) {
            if (this->m_Event.GetEventType() == T::GetStaticType()) {
                this->m_Event.Handled |= func(static_cast<T&>(this->m_Event));

                return true;
            }

            return false;
        }

    private:
        /** @brief The Event to dispatch. */
        Event& m_Event;

    };  // EventDispatcher

}   // Ocean
