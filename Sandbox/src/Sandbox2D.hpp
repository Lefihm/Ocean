#pragma once

#include <Ocean/Core/Layers/Layer.hpp>
#include <Ocean/Platform/Events/Event.hpp>

class Sandbox2D : public Ocean::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;

	virtual void OnEvent(Ocean::Event& e) override;

private:

};  // Sandbox2D
