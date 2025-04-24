#pragma once

// Ocean
#include "Ocean/Core/Exceptions.hpp"

#include "Ocean/Core/Application.hpp"

#include "Ocean/Core/Service/ServiceRegistry.hpp"

// std
#include <exception>
#include <iostream>

extern Ocean::Application* Ocean::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
    Ocean::StaticServiceRegistry::InitializeServices();

    Ocean::Application* app = Ocean::CreateApplication(argc, argv);

    try {
        app->Run();
    }
    catch (const Ocean::Exception& e) {
        std::cerr << "Ocean Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    delete app;
    Ocean::StaticServiceRegistry::ShutdownServices();

    return EXIT_SUCCESS;
}
