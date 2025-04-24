/**
 * @file MemoryService.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"

#include "Ocean/Primitives/Memory/Common.hpp"
#include "Ocean/Primitives/Memory/Heap.hpp"
#include "Ocean/Primitives/Memory/Malloc.hpp"

#include "Ocean/Core/Service.hpp"

namespace Ocean {

    /**
    * @brief A struct that holds stats about memory allocations in the lifetime.
    */
    struct MemoryStats {

        sizet allocatedBytes; /** @brief The total number of bytes allocated in the stat's lifetime. */
        sizet freedBytes; /** @brief The total number of bytes freed in the stat's lifetime. */

        u32 allocationCount; /** @brief The number of allocations made in the stat's lifetime. */
        u32 freeCount; /** @brief The number of frees made in the stat's lifetime. */

        /**
        * @brief Add's data to the stat's such as the total allocatedBytes and the allocationCount. 
        * 
        * @param a The number of bytes to add.
        * @return The original value.
        */
        sizet Add(sizet a) {
            if (a) {
                this->allocatedBytes += a;
                this->allocationCount++;
            }

            return a;
        }

        /**
        * @brief Add's data to the stat's such as the total freedBytes and the freeCount.
        * 
        * @param a The number of bytes to "remove".
        * @return The original value.
        */
        sizet Remove(sizet a) {
            if (a) {
                this->freedBytes += a;
                this->freeCount++;
            }

            return a;
        }

    };    // MemoryStats



    /**
    * @brief A struct that can be used to configure the MemoryService outside of defaults.
    */
    struct MemoryServiceConfig {

        sizet MaxDynamicSize = omega(16); /** @brief Default size of 16MB of dynamic memory. */

    };    // MemoryServiceConfig

    /**
    * @brief The primary service to interact with to get memory in Ocean.
    */
    class MemoryService : public StaticService<MemoryService> {
    public:
        MemoryService();
        virtual ~MemoryService() = default;

        AssignServiceName(MemoryService);
        AssignServicePriority(ServicePriority::IMMEDIATE);

        /**
        * @brief Get's the instance of the MemoryService.
        * 
        * @return MemoryService& 
        */
        static MemoryService* Instance();

        /**
        * @brief Initializes the MemoryService and its allocators.
        */
        virtual void Init() override;
        /**
        * @brief Shuts down the MemoryService and its allocators.
        */
        virtual void Shutdown() override;

        /**
        * @brief Get's the system allocator of Ocean. I.e. the allocator used internally.
        * 
        * @return Allocator* 
        */
        Allocator* SystemAllocator()    { return &m_SystemAllocator; }
        /**
        * @brief Get's the system allocator of the System. Which is unmanaged by Ocean.
        * 
        * @return Allocator* 
        */
        Allocator* UnmanagedAllocator() { return &m_MallocAllocator; }

    private:
        /** @brief The MemoryService instance pointer. */
        inline static MemoryService* s_Instance =  nullptr;

        /** @brief The HeapAllocator for Ocean's core allocations. */
        HeapAllocator m_SystemAllocator;
        /** @brief The unmanaged allocator that uses malloc and free. */
        MallocAllocator m_MallocAllocator;

    };    // MemoryService

}    // Ocean

/** @todo STL compliant allocator that routes to Ocean allocators. Example code at: https://howardhinnant.github.io/allocator_boilerplate.html */
