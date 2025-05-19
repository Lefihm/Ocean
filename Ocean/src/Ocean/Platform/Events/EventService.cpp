#include "EventService.hpp"

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/SmartPtrs.hpp"

#include "Ocean/Core/Exceptions.hpp"

#include "Ocean/Platform/Events/Event.hpp"

// libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {

    EventService::EventService() :
        RuntimeService(),
        m_Events(),
        m_Callbacks(static_cast<u16>(EventCategory::EVENT_CATEGORY_MAX) - 1)
    {
        if (!this->s_Instance)
            this->s_Instance = this;
    }

    EventService::~EventService()
    {
        
    }

    void EventService::Init() {
        if (!s_Instance)
            throw Exception(Error::BAD_INSTANCE, "EventService Instance Is Not Valid!");
    }

    void EventService::Shutdown() {
        this->m_Callbacks.clear();
    }

    void EventService::SignalEvent(Scope<Event> e) {
        s_Instance->m_Events.push(std::move(e));
    }

    void EventService::DispatchEvents() {
        while (!s_Instance->m_Events.empty()) {
            Scope<Event>& e = s_Instance->m_Events.front();
            u8 flags = e->GetCategoryFlags();

            if (flags & EventCategoryFlags::APPLICATION && s_Instance->DispatchEvent(*e, EventCategory::APPLICATION)) {
                s_Instance->m_Events.pop(); continue;
            }
            if (flags & EventCategoryFlags::WINDOW && s_Instance->DispatchEvent(*e, EventCategory::WINDOW)) {
                s_Instance->m_Events.pop(); continue;
            }

            s_Instance->m_Events.pop();
        }
    }

    b8 EventService::DispatchEvent(Event& e, EventCategory category) {
        if (this->m_Callbacks[category].Empty())
            return false;

        for (EventCallback_T& callback : this->m_Callbacks[category]) {
            callback(e);

            if (e.Handled)
                return true;
        }

        return false;
    }

}   // Ocean
