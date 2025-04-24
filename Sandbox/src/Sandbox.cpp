#include "Sandbox2D.hpp"

#include <Ocean/Core/EntryPoint.hpp>
#include <Ocean/Core/Logger.hpp>

class Sandbox : public Ocean::Application {
public:
	Sandbox(const Ocean::ApplicationConfig& config);
	~Sandbox();

};	// Sandbox



Ocean::Application* Ocean::CreateApplication(int argc, char** argv) {
	Ocean::ApplicationConfig config("Ocean Sandbox", 1200, 800);

	return new Sandbox(config);
}



Sandbox::Sandbox(const Ocean::ApplicationConfig& config) : Ocean::Application(config) {
	oprint(CONSOLE_TEXT_CYAN("Constructing Sandbox Application!\n"));

	PushLayer(new Sandbox2D);
}

Sandbox::~Sandbox() {
	oprint(CONSOLE_TEXT_CYAN("Deconstructing Sandbox Application!\n"));	
}
