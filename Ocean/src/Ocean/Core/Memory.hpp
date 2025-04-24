/**
 * @file Memory.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

/** @brief Macro to get the system allocator from the MemoryService. */
#define oSystemAllocator      MemoryService::Instance()->SystemAllocator()
/** @brief Macro to get the unmanaged allocator from the MemoryService. */
#define oUnmanagedAllocator   MemoryService::Instance()->UnmanagedAllocator()

#if OC_VERBOSE_MEMORY

    /** @brief Macro to allocate a chunk of memory of the given size from the given allocator. (VERBOSE implementation). @returns void* */
    #define oalloca(size, allocator)             ((allocator)->Allocate(size, 1)); oprintret(OCEAN_FUNCTIONLINE("Allocation Made!"))
    /** @brief Macro to allocate a chunk of memory of the given size from the given allocator. (VERBOSE implementation). @returns u8* */
    #define oallocam(size, allocator)             (static_cast<u8*>((allocator)->Allocate(size, 1)); oprintret(OCEAN_FUNCTIONLINE("Mapped Allocation Made!"))
    /** @brief Macro to allocate an array of memory of the given type and count from the given allocator. (VERBOSE implementation). @returns type* */
    #define oallocat(type, count, allocator)     (static_cast<type*>((allocator)->Allocate(sizeof(type) * count, alignof(type)))); oprintret(OCEAN_FUNCTIONLINE("Type Allocation Made!"))

    /** @brief Macro to allocate a chunk of memory of the given size from the given allocator with the given alignment. (VERBOSE implementation). @returns void* */
    #define oallocaa(size, allocator, alignment) ((allocator)->Allocate(size, alignment)); oprintret(OCEAN_FUNCTIONLINE("Aligned Allocation Made!"))

    /** @brief Macro to deallocate a chunk of memory from the given allocator with the given pointer. (VERBOSE implementation). */
    #define ofree(pointer, allocator)             ((allocator)->Deallocate(pointer)); oprintret(OCEAN_FUNCTIONLINE("Memory Freed!"))

#else

    /** @brief Macro to allocate a chunk of memory of the given size from the given allocator. @returns void* */
    #define oalloca(size, allocator)             ((allocator)->Allocate(size, 1))
    /** @brief Macro to allocate a chunk of memory of the given size from the given allocator. @returns u8* */
    #define oallocam(size, allocator)             (static_cast<u8*>((allocator)->Allocate(size, 1))
    /** @brief Macro to allocate an array of memory of the given type and count from the given allocator. @returns type* */
    #define oallocat(type, count, allocator)     (static_cast<type*>((allocator)->Allocate(sizeof(type) * count, alignof(type))))

    /** @brief Macro to allocate a chunk of memory of the given size from the given allocator with the given alignment. @returns void* */
    #define oallocaa(size, allocator, alignment) ((allocator)->Allocate(size, alignment))

    /** @brief Macro to deallocate a chunk of memory from the given allocator with the given pointer. */
    #define ofree(pointer, allocator)             ((allocator)->Deallocate(pointer))

#endif
