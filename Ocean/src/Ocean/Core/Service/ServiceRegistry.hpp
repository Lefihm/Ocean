/**
 * @file ServiceRegistry.hpp
 * @brief Service and class registration utilities for Ocean.
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"
#include "Ocean/Types/SmartPtrs.hpp"
#include "Ocean/Types/Strings.hpp"

// std
#include <vector>

namespace Ocean {

    // Code Adapted From:
    //  https://gist.github.com/jcarrano/39f5acbf3d94aeed802bda15aa7e79f9

    /**
     * @brief Base class for registrators, enabling polymorphic storage.
     */
    class BaseRegistrator {
    public:
        BaseRegistrator() = default;
        virtual ~BaseRegistrator() = default;

        inline virtual void Init() { }
        inline virtual void Shutdown() { }

    };  // BaseRegistrator

    /**
    * @brief Represents a registered service entry, storing its name, priority, and instance.
    */
    struct RegistryEntryData {
        /** @brief Name of the registered service. */
        cstring name;
        /** @brief Priority of the registered service. */
        u8 priority;

        /** @brief Pointer to the registered service instance. */
        Ref<BaseRegistrator> data;

    };  // RegistryEntryData

    /**
     * @brief Template for a class registry.
     *
     * @tparam Container The container type used to store registered classes.
     * @tparam CRTP The derived registry type (CRTP pattern).
     */
    template <typename Container, typename CRTP>
    class ClassRegistry {
    public:
        /**
         * @brief Returns the container holding all registered classes.
         * 
         * @return const Container& Reference to the container of registered classes.
         */
        inline static constexpr const Container& Classes() { return _Classes(); }

        /**
         * @brief Helper for registering a class at static initialization.
         * 
         * @details Declaring a static member of this type in a class will
         *          automatically register it in the registry at static initialization.
         * 
         * @tparam SubClass The class to register.
         */
        template <class SubClass>
        class Registrator {
        public:
            inline constexpr Registrator() {
                ClassRegistry::AccessRegisterImpl::template RegisterClass<SubClass>();
            }

        };  // Registrator

    protected:
        template <class SubClass> friend class Registrator;

    protected:
        /**
         * @brief Internal helper struct to provide access to RegisterClass.
         */
        struct AccessRegisterImpl : CRTP {
            /**
             * @brief Registers a class in the registry.
             * 
             * @tparam Class The class to register.
             */
            template <typename Class>
            inline static constexpr void RegisterClass() { CRTP::template RegisterClass<Class>(); }

        };  // AccessRegisterImpl

    protected:
        /**
         * @brief Internal accessor for the static container.
         *
         * @details Using a static function avoids static initialization order issues.
         * 
         * @return ContainerT& Reference to the static container.
         */
        inline static Container& _Classes() {
            static Container c { };

            return c;
        }

        /**
         * @brief Registers a service class in the registry, ordered by priority.
         * 
         * @tparam Service The service type to register.
         */
        template <typename Service>
        inline static void RegisterClass() {
            auto& classes = _Classes();

            // Prevent duplicate registration by name
            for (const auto& entry : classes)
                if (entry.name == Service::Name())
                    return;

            RegistryEntryData newEntry {
                Service::Name(),
                Service::Priority(),
                MakeRef<Service>()
            };

            auto it = classes.begin();

            // Find the correct insertion point: after last with <= priority
            for (; it != classes.end(); ++it)
                if (it->priority > Service::Priority())
                    break;

            // Insert the new entry at the found position
            classes.insert(it, newEntry);
        }

    };  // ClassRegistry

    /**
     * @brief Registers a class with a given registry using CRTP.
     * 
     * @details Instantiating this template registers the derived class in the specified registry.
     * 
     * @tparam RegistryClass The registry to register with.
     * @tparam CRTP The derived class type.
     */
    template <typename RegistryClass, typename CRTP>
    class Registrator : public BaseRegistrator {
    public:
        using RegistratorT = typename RegistryClass::template Registrator<CRTP>;

    #ifdef __clang__

        /**
         * @brief Ensures Clang instantiates the static member variable.
         */
        inline static RegistratorT& _ClangAttribute() __attribute__((used)) {
            return s_Registrator;
        }

    #endif

    private:
        /** @brief Static member to trigger registration at static initialization. */
        inline static RegistratorT s_Registrator __attribute__((used)) { };

    };  // Registrator

    /**
     * @brief Registry for services with a lifetime outside the Ocean application.
     */
    class StaticServiceRegistry : public ClassRegistry<std::vector<RegistryEntryData>, StaticServiceRegistry> {
    public:
        /**
         * @brief Initializes all registered static services.
         */
        static void InitializeServices();

        /**
         * @brief Shuts down all registered static services.
         */
        static void ShutdownServices();

    };  // ServiceRegistry

    /**
     * @brief Registry for services with a lifetime within the Ocean application.
     */
    class RuntimeServiceRegistry : public ClassRegistry<std::vector<RegistryEntryData>, RuntimeServiceRegistry> {
    public:
        /**
         * @brief Initializes all registered runtime services.
         */
        static void InitializeServices();

        /**
         * @brief Shuts down all registered runtime services.
         */
        static void ShutdownServices();

    };  // ServiceRegistry

}   // Ocean
