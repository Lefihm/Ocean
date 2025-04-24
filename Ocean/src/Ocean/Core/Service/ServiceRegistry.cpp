#include "ServiceRegistry.hpp"

#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Logger.hpp"

// std
#include <utility>

namespace Ocean {

    void StaticServiceRegistry::InitializeServices() {
        for (std::pair<cstring, Ref<BaseRegistrator>> service : _Classes()) {
            oprint("|> Initializing %s\n", service.first);

            service.second->Init();
        }
    }

    void StaticServiceRegistry::ShutdownServices() {
        for (std::pair<cstring, Ref<BaseRegistrator>> service : _Classes()) {
            oprint("|> Shutting Down %s\n", service.first);

            service.second->Shutdown();
        }
    }

    void RuntimeServiceRegistry::InitializeServices() {
        for (std::pair<cstring, Ref<BaseRegistrator>> service : _Classes()) {
            oprint("|> Initializing %s", service.first);

            service.second->Init();
        }
    }

    void RuntimeServiceRegistry::ShutdownServices() {
        for (std::pair<cstring, Ref<BaseRegistrator>> service : _Classes()) {
            oprint("|> Shutting Down %s", service.first);

            service.second->Shutdown();
        }
    }

}   // Ocean
