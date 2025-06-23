/**
 * @file ServiceRegistry.hpp
 * @brief 
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
#include <iostream>
#include <vector>

namespace Ocean {

    // Code Adapted From:
    //  https://gist.github.com/jcarrano/39f5acbf3d94aeed802bda15aa7e79f9

    /**
     * @brief A class registry template.
     *
     * @tparam Container The container type of the registry.
     * @tparam CRTP Class Registry Type
     */
    template <typename Container, typename CRTP>
    class ClassRegistry {
    public:
        using ContainerT = Container;

        /**
         * @brief Gets the container of classes.
         * 
         * @return const ContainerT& 
         */
        inline static constexpr const ContainerT& Classes() { return _Classes(); }

        /**
         * @brief Holds a class in a registry collector class.
         * 
         * @details By declaring a static member using this template,
         *          the containing class will be added to a container
         *          at static-runtime.
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
         * @brief Structure to protect the RegisterClass function.
         */
        struct AccessRegisterImpl : CRTP {
            /**
             * @brief Registers a class to the registry.
             * 
             * @tparam Class The class to register.
             */
            template <typename Class>
            inline static constexpr void RegisterClass() { CRTP::template RegisterClass<Class>(); }
        };  // AccessRegisterImpl

    protected:
        /**
         * @brief Internal container access.
         *
         * @details By using a static method instead of a member problems
         *          with initialization order are avoided.
         * 
         * @return ContainerT& 
         */
        inline static ContainerT& _Classes() {
            static ContainerT c { };

            return c;
        }

    };  // ClassRegistry

    /**
     * @brief Base non-templated registrator to enable pointer storage.
     */
    class BaseRegistrator {
    public:
        BaseRegistrator() = default;
        virtual ~BaseRegistrator() = default;

        inline virtual void Init() { };
        inline virtual void Shutdown() { };

    };  // BaseRegistrator

    /**
     * @brief Intermediary that registers classes to the given registry.
     * 
     * @details When this template is instantiated, the derived class will
     *          be registered in RegistryClass.
     * 
     * @tparam RegistryClass The registry to use.
     * @tparam CRTP Class Registry Type
     */
    template <typename RegistryClass, typename CRTP>
    class Registrator : public BaseRegistrator {
    public:
        using RegistratorT = typename RegistryClass::template Registrator<CRTP>;

    #ifdef __clang__

        /**
         * @brief Clang "used" attribute of a static member variable does not instantiate
         *        the same so a accessor is needed.
         */
        inline static RegistratorT& _ClangAttribute() __attribute__((used)) {
            return s_Registrator;
        }

    #endif

    private:
        /** @brief A static member variable to instantiate the class in the registry. */
        inline static RegistratorT s_Registrator __attribute__((used)) { };

    };  // Registrator

    /**
     * @brief A struct representing a registry entity, storing the name, priority, and the registered class.
     */
    struct RegistryEntryData {
        cstring name;
        u8 priority;

        Ref<BaseRegistrator> data;

    };  // RegistryEntryData

    /**
     * @brief A registery of Services that have a lifetime outside of the Ocean Applicaiton.
     */
    class StaticServiceRegistry : public ClassRegistry<std::vector<RegistryEntryData>, StaticServiceRegistry> {
    public:
        /**
         * @brief Initializes the registered services.
         */
        static void InitializeServices();
         /**
          * @brief Shuts down the registered services.
          */
        static void ShutdownServices();

    protected:
        /**
         * @brief Registers a service class to the registry.
         * 
         * @tparam Service The service type to register.
         */
        template <typename Service>
        inline static void RegisterClass() {
            if (_Classes().empty() || _Classes().back().priority < Service::Priority()) {
                _Classes().emplace_back(RegistryEntryData { Service::Name(), Service::Priority(), MakeRef<Service>() });
            }
            else if (_Classes().front().priority > Service::Priority()) {
                _Classes().emplace(_Classes().begin(), RegistryEntryData { Service::Name(), Service::Priority(), MakeRef<Service>() });
            }
            else {
                for (u16 i = 1; i < _Classes().size(); i++) {
                    if (_Classes()[i - 1].priority < Service::Priority()) {
                        _Classes().emplace(_Classes().begin() + i, RegistryEntryData { Service::Name(), Service::Priority(), MakeRef<Service>() });

                        break;
                    }
                }
            }
        }

    };  // ServiceRegistry

    /**
     * @brief A registry of Services that have a lifetime within the Ocean Application.
     */
    class RuntimeServiceRegistry : public ClassRegistry<std::vector<RegistryEntryData>, RuntimeServiceRegistry> {
    public:
        /**
         * @brief Initializes the registered services.
         */
        static void InitializeServices();
         /**
          * @brief Shuts down the registered services.
          */
        static void ShutdownServices();

    protected:
        /**
         * @brief Registers a service class to the registry.
         * 
         * @tparam Service The service type to register.
         */
        template <typename Service>
        inline static void RegisterClass() {
            if (_Classes().empty() || _Classes().back().priority < Service::Priority())
                _Classes().emplace_back(RegistryEntryData { Service::Name(), Service::Priority(), MakeRef<Service>() });
            else if (_Classes().front().priority > Service::Priority())
                _Classes().emplace(_Classes().begin(), RegistryEntryData { Service::Name(), Service::Priority(), MakeRef<Service>() });
            else {
                for (u16 i = 1; i < _Classes().size(); i++)
                    if (_Classes()[i].priority < Service::Priority())
                        _Classes().emplace(_Classes().begin() + i - 1, RegistryEntryData { Service::Name(), Service::Priority(), MakeRef<Service>() });
            }
        }

    };  // ServiceRegistry

}   // Ocean
