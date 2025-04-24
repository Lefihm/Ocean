#include "Malloc.hpp"

// std
#include <cstdlib>

void* MallocAllocator::Allocate(sizet size, sizet alignment) {
    return malloc(size);
}

void MallocAllocator::Deallocate(void* ptr) {
    free(ptr);
}