#include "Heap.hpp"

// libs
#include <tlsf.h>

// std
#include <cstdlib>

#ifdef OC_VERBOSE

    #include "Ocean/Core/Logger.hpp"

    static void ExitWalker(void* ptr, sizet size, i32 used, OC_UNUSED void* user) {
        if (used) {
            oprint("Found active allocation %p, %llu\n", ptr, size);
        }
    }

#endif

// Heap Allocator

#ifdef OC_VERBOSE

    static MemoryStats s_Stats{ 0, 0, 0, 0 };

#endif

HeapAllocator::~HeapAllocator() { }

void HeapAllocator::Init(sizet size) {
    this->p_Memory = malloc(size);
    this->m_TotalSize = size;
    this->m_AllocatedSize = 0;

    this->p_Handle = tlsf_create_with_pool(this->p_Memory, size);
}

void HeapAllocator::Shutdown() {
#ifdef OC_VERBOSE
    if (s_Stats.allocatedBytes != s_Stats.freedBytes)
        oprint(CONSOLE_TEXT_RED("Allocations still present. Check your code!\n"));

    void* pool = tlsf_get_pool(this->p_Handle);
    tlsf_walk_pool(pool, ExitWalker, static_cast<void*>(&s_Stats));

    oprint(CONSOLE_TEXT_CYAN("Memory Heap Stats:\n"));
    oprint(CONSOLE_TEXT_CYAN("\tAllocated Bytes: %i\n"), s_Stats.allocatedBytes);
    oprint(CONSOLE_TEXT_CYAN("\tFreed Bytes: %i\n"), s_Stats.freedBytes);
    oprint(CONSOLE_TEXT_CYAN("\tTotal Allocations: %i\n"), s_Stats.allocationCount);
    oprint(CONSOLE_TEXT_CYAN("\tTotal Free's: %i\n"), s_Stats.freeCount);

#endif

    tlsf_destroy(this->p_Handle);

    free(this->p_Memory);
    this->p_Memory = this->p_Handle = nullptr;
    this->m_TotalSize = this->m_AllocatedSize = 0;
}

void* HeapAllocator::Allocate(sizet size, sizet alignment) {
#ifdef OC_VERBOSE

    void* allocatedMemory = alignment == 1 ? tlsf_malloc(this->p_Handle, size) : tlsf_memalign(this->p_Handle, alignment, size);
    this->m_AllocatedSize += s_Stats.Add(tlsf_block_size(allocatedMemory));

    return allocatedMemory;

#else

    return tlsf_malloc(this->p_Handle, size);

#endif
}

void HeapAllocator::Deallocate(void* ptr) {
#ifdef OC_VERBOSE

    this->m_AllocatedSize -= s_Stats.Remove(tlsf_block_size(ptr));

    tlsf_free(this->p_Handle, ptr);

#else

    tlsf_free(this->p_Handle, ptr);

#endif
}