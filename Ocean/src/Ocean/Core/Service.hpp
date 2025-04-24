/**
 * @file Service.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Core/Macros.hpp"

#include "Ocean/Core/Service/ServiceRegistry.hpp"

namespace Ocean {

    /**
     * @brief Unified priorities, used to determine Service initialization order.
     */
    typedef enum ServicePriority {
        IMMEDIATE = 0,
        INITIAL   = 1,
        DONT_CARE = 2

    } ServicePriority;

    /** @brief Assigns the given Service name. */
    #define AssignServiceName(service) inline static constexpr cstring Name() { return OCEAN_CONCAT("Ocean_", OCEAN_MAKESTRING(service)); }
    /** @brief Assigns the priority of the Service. It is recommended to use the ServicePriority enum. */
    #define AssignServicePriority(priority) inline static constexpr u8 Priority() { return priority; }

    /**
     * @brief A static service base class. Handles service registry.
     * 
     * @tparam SRTP Service Registry Type
     */
    template <class SRTP>
    class StaticService : public Registrator<StaticServiceRegistry, SRTP> {
    public:
        AssignServiceName(StaticService);
        AssignServicePriority(ServicePriority::DONT_CARE);

    };  // StaticService

    /**
     * @brief A runtime service base class. Handles service registry.
     * 
     * @tparam SRTP Service Registry Type
     */
    template <class SRTP>
    class RuntimeService : public Registrator<RuntimeServiceRegistry, SRTP> {
    public:
        AssignServiceName(RuntimeService);
        AssignServicePriority(ServicePriority::DONT_CARE);

    };  // RuntimeService

}   // Ocean
