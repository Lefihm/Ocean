#include "Sandbox2D.hpp"

#include <Ocean/Core/Logger.hpp>

#include <Ocean/Platform/Events/EventService.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D")
{ }

void Sandbox2D::OnAttach() {
    oprint("Sandbox Layer Attach: {%s}\n", this->GetName().c_str());

    /**
    * @todo For some reason the EventService instance is resetting to 0x0000...
    *       need to investigate as to why because there is no reason it should.
    */

    // Ocean::EventService::AddEventCallback<Ocean::EventCategory::KEYBOARD>(OC_BIND_EVENT_FN(Sandbox2D::OnEvent));
}

void Sandbox2D::OnDetach() {
    // Ocean::EventService::RemoveEventCallback<Ocean::EventCategory::KEYBOARD>(OC_BIND_EVENT_FN(Sandbox2D::OnEvent));

    oprint("Sandbox Layer Detach: {%s}\n", this->GetName().c_str());
}

void Sandbox2D::OnUpdate(Timestep ts) {
    
}

void Sandbox2D::OnEvent(Ocean::Event& e) {
    oprint("Recieved event: {%s}", e.GetEventName());
}
