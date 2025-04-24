/**
 * @file Service.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Macros.hpp"

#include "Ocean/Core/Service/ServiceRegistry.hpp"

namespace Ocean {

    #define AssignServiceName(service) inline static constexpr cstring Name() { return OCEAN_CONCAT("Ocean_", OCEAN_MAKESTRING(service)); }

    /**
     * @brief A service base class. Handles service registry.
     * 
     * @tparam SRTP Service Registry Type
     */
    template <class SRTP>
    class StaticService : public Registrator<StaticServiceRegistry, SRTP> {
    public:
        AssignServiceName(StaticService);

    };  // StaticService

    /**
     * @brief A service base class. Handles service registry.
     * 
     * @tparam SRTP Service Registry Type
     */
    template <class SRTP>
    class RuntimeService : public Registrator<RuntimeServiceRegistry, SRTP> {
    public:
        AssignServiceName(Service);

    };  // Service

}   // Ocean
