#include "MemoryService.hpp"

#include "Ocean/Primitives/Memory/Heap.hpp"

// libs
#include <tlsf.h>

// std
#include <stdlib.h>
#include <cstring>

namespace Ocean {

    static sizet s_Size = omega(32) + tlsf_size() + 8;

    MemoryService::MemoryService() :
        StaticService(),
        m_SystemAllocator(),
        m_MallocAllocator()
    {
        if (!s_Instance)
            s_Instance = this;
    }

    MemoryService* MemoryService::Instance() {
        return s_Instance;
    }

    void MemoryService::Init() {
        this->m_SystemAllocator.Init(s_Size);
    }

    void MemoryService::Shutdown() {
        this->m_SystemAllocator.Shutdown();
    }

}   // Ocean
