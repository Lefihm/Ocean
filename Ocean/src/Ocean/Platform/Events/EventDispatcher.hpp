#pragma once

#include "Ocean/Types/Bool.hpp"

#include "Event.hpp"

namespace Ocean {

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) :
            m_Event(event)
        { }

        template <typename T, typename F>
        b8 Dispatch(const F& func) {
            if (this->m_Event.GetEventType() == T::GetStaticType()) {
                this->m_Event.Handled |= func(static_cast<T&>(this->m_Event));

                return true;
            }

            return false;
        }

    private:
        Event& m_Event;

    };  // EventDispatcher

}   // Ocean
