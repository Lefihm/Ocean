#include "EventService.hpp"

#include "Ocean/Core/Logger.hpp"

// libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {

    EventService::EventService() :
        RuntimeService()
    {
        
    }

    EventService::~EventService()
    {
        
    }

    void EventService::Init() {

    }

    void EventService::Shutdown() {
        
    }

    void EventService::SignalEvent(Event& e) {
        switch (e.GetEventLevel()) {
            case NONE:
                oprints("Event attempted to be signaled that has an invalid EventLevel!");
                break;

            case SYSTEM:

                break;

            case APPLICATION:

                break;

            case USER:

                break;
        }
    }

    void EventService::AddEventCallback(EventLevel level, EventCallback_T callback) {
        switch (level) {
            case NONE:
                oprints("Event callback attempted to be added that has an invalid EventLevel!"); break;

            case SYSTEM:
                this->m_SystemCallbacks.EmplaceBack(callback);      break;

            case APPLICATION:
                this->m_ApplicationCallbacks.EmplaceBack(callback); break;

            case USER:
                this->m_UserCallbacks.EmplaceBack(callback);        break;
        }
    }

    void EventService::DispatchEvents() {
        
    }

}   // Ocean
