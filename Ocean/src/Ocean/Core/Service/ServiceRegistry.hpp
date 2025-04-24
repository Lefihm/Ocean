/**
 * @file ServiceRegistry.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/SmartPtrs.hpp"
#include "Ocean/Types/Strings.hpp"

#include "Ocean/Primitives/HashMap.hpp"

#include "Ocean/Core/Exceptions.hpp"

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
     * @brief 
     */
    class StaticServiceRegistry : public ClassRegistry<UnorderedMap<cstring, Ref<BaseRegistrator>>, StaticServiceRegistry> {
    protected:
        /**
         * @brief 
         * 
         * @tparam Service The service type to register.
         */
        template <typename Service>
        inline static void RegisterClass() {
            if (_Classes().find(Service::Name()) != _Classes().end())
                throw Exception(Error::DUPLICATE_DATA, "Attempting to register Service when it is already registered!");

            _Classes().try_emplace(Service::Name(), MakeRef<Service>());
        }

        /**
         * @brief 
         */
        static void InitializeServices();
        /**
         * @brief 
         */
        static void ShutdownServices();

    };  // ServiceRegistry

    /**
     * @brief 
     */
    class RuntimeServiceRegistry : public ClassRegistry<UnorderedMap<cstring, Ref<BaseRegistrator>>, RuntimeServiceRegistry> {
    protected:
        /**
         * @brief 
         * 
         * @tparam Service The service type to register.
         */
        template <typename Service>
        inline static void RegisterClass() {
            if (_Classes().find(Service::Name()) != _Classes().end())
                throw Exception(Error::DUPLICATE_DATA, "Attempting to register Service when it is already registered!");

            _Classes().try_emplace(Service::Name(), MakeRef<Service>());
        }

        /**
         * @brief 
         */
        static void InitializeServices();
        /**
         * @brief 
         */
        static void ShutdownServices();

    };  // ServiceRegistry

}   // Ocean
