#include "EventService.hpp"

#include "Ocean/Platform/Events/Event.hpp"

// libs
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Ocean {

    EventService::EventService() :
        RuntimeService()
    {
        if (!this->s_Instance)
            this->s_Instance = this;
    }

    EventService::~EventService()
    {
        
    }

    void EventService::Init() {

    }

    void EventService::Shutdown() {
        
    }

    EventService* EventService::Instance() {
        return s_Instance;
    }

    void EventService::SignalEvent(Event& e) {

    }

    void EventService::AddEventCallback(EventCategory category, const EventCallback_T& callback) {

    }

    void EventService::DispatchEvents() {
        
    }

}   // Ocean
