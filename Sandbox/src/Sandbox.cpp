#include "Sandbox2D.hpp"

#include <Ocean/Core/EntryPoint.hpp>
#include <Ocean/Core/Logger.hpp>

#include <Ocean/Platform/Window/WindowService.hpp>

class Sandbox : public Ocean::Application {
public:
    Sandbox(const Ocean::ApplicationConfig& config);
    ~Sandbox();

};    // Sandbox



Ocean::Application* Ocean::CreateApplication(int argc, char** argv) {
    Ocean::ApplicationConfig config(
        "Ocean Sandbox",
        argc,
        argv
    );

    return new Sandbox(config);
}



Sandbox::Sandbox(const Ocean::ApplicationConfig& config) : Ocean::Application(config) {
    oprint(CONSOLE_TEXT_MAGENTA("Constructing Sandbox Application\n"));

    Ocean::WindowService::MakeWindow(800, 600, "Sandbox");

    PushLayer(new Sandbox2D);
}

Sandbox::~Sandbox() {
    oprint(CONSOLE_TEXT_MAGENTA("Deconstructing Sandbox Application\n"));
}
