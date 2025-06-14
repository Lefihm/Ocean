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
    enum ServicePriority : u8 {
        IMMEDIATE = 0,
        INITIAL   = 1,
        DONT_CARE = 2

    };

    /** @brief Assigns the given Service name. */
    #define AssignServiceName(service) inline static constexpr cstring Name() { return OCEAN_MAKESTRING(service); }
    /** @brief Assigns the priority of the Service. It is recommended to use the ServicePriority enum. */
    #define AssignServicePriority(priority) inline static constexpr u8 Priority() { return static_cast<u8>(priority); }

    /**
     * @brief A static service base class. Handles service registry.
     * 
     * @tparam SRTP Service Registry Type
     */
    template <class SRTP>
    class StaticService : public Registrator<StaticServiceRegistry, SRTP> { };  // StaticService

    /**
     * @brief A runtime service base class. Handles service registry.
     * 
     * @tparam SRTP Service Registry Type
     */
    template <class SRTP>
    class RuntimeService : public Registrator<RuntimeServiceRegistry, SRTP> { };  // RuntimeService

}   // Ocean
