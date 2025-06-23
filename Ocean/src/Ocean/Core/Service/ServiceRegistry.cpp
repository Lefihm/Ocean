#include "ServiceRegistry.hpp"

#include "Ocean/Core/Macros.hpp"

#include "Ocean/Core/Logger.hpp"

namespace Ocean {

    void StaticServiceRegistry::InitializeServices() {
        for (const RegistryEntryData& service : _Classes()) {
            oprint("|-> Initializing %s, priority %i\n", service.name, service.priority);

            service.data->Init();
        }
    }

    void StaticServiceRegistry::ShutdownServices() {
        for (i16 i = _Classes().size() - 1; i >= 0; i--) {
            oprint("|-> Shutting Down %s\n", _Classes()[i].name);

            _Classes()[i].data->Shutdown();
        }
    }

    void RuntimeServiceRegistry::InitializeServices() {
        for (const RegistryEntryData& service : _Classes()) {
            oprint(CONSOLE_TEXT_CYAN("|-> Initializing %s, priority %i\n"), service.name, service.priority);

            service.data->Init();
        }
    }

    void RuntimeServiceRegistry::ShutdownServices() {
        for (i16 i = _Classes().size() - 1; i >= 0; i--) {
            oprint(CONSOLE_TEXT_CYAN("|-> Shutting Down %s\n"), _Classes()[i].name);

            _Classes()[i].data->Shutdown();
            _Classes()[i].data.reset();
        }
    }

}   // Ocean
