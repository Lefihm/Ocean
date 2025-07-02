#include "Sandbox2D.hpp"

#include <Ocean/Core/Logger.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") {

}

void Sandbox2D::OnAttach() {
    // Ocean::EventService::AddEventCallback<Ocean::EventCategory::APPLICATION>(OC_BIND_EVENT_FN(Sandbox2D::OnEvent));

    oprint("Sandbox Layer Name: {%s}\n", this->GetName().c_str());
}

void Sandbox2D::OnDetach() {
    // TODO Remove event callback
    // Ocean::EventService::RemoveEventCallback<Ocean::EventCategory::APPLICATION>(OC_BIND_EVENT_FN(Sandbox2D::OnEvent));

    oprint("Sandbox Layer Detach\n");
}

void Sandbox2D::OnUpdate(Timestep ts) {
    
}

void Sandbox2D::OnEvent(Ocean::Event& e) {
    oprint("Recieved event: {%s}", e.GetEventName());
}
