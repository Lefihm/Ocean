#include "EventService.hpp"

#include "Ocean/Core/Logger.hpp"

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
        switch (e.GetEventType()) {
            case EventType::NONE:               oprints("EventType %s\n", e.GetEventName());
            case EventType::APP_SHOULD_CLOSE:   oprints("EventType %s\n", e.GetEventName());
            case EventType::WINDOW_CLOSE:       oprints("EventType %s\n", e.GetEventName());
            case EventType::WINDOW_RESIZE:      oprints("EventType %s\n", e.GetEventName());
            case EventType::WINDOW_REFRESH:     oprints("EventType %s\n", e.GetEventName());
            case EventType::WINDOW_FOCUSED:     oprints("EventType %s\n", e.GetEventName());
            case EventType::WINDOW_LOST_FOCUS:  oprints("EventType %s\n", e.GetEventName());
            case EventType::KEY_PRESSED:        oprints("EventType %s\n", e.GetEventName());
            case EventType::KEY_RELEASED:       oprints("EventType %s\n", e.GetEventName());
            case EventType::KEY_TYPED:          oprints("EventType %s\n", e.GetEventName());
            case EventType::MOUSE_PRESSED:      oprints("EventType %s\n", e.GetEventName());
            case EventType::MOUSE_RELEASED:     oprints("EventType %s\n", e.GetEventName());
            case EventType::MOUSE_MOVED:        oprints("EventType %s\n", e.GetEventName());
            case EventType::MOUSE_SCROLLED:     oprints("EventType %s\n", e.GetEventName());
            }
    }

    void EventService::AddEventCallback(EventCategory category, const EventCallback_T& callback) {

    }

    void EventService::DispatchEvents() {
        
    }

}   // Ocean
