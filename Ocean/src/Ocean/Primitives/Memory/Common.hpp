/**
 * @file Common.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"

// std
#include <stdint.h>

#define okilo(size) (size * 1024)
#define omega(size) (size * 1024 * 1024)
#define ogiga(size) (size * 1024 * 1024 * 1024)

// The following offset and adjustment implementations are adapted from:
// https://screwjankgames.github.io/engine%20programming/2020/09/24/writing-your-own-memory-allocators.html

inline uintptr_t oAlignmentOffset(sizet alignOf, const void* const ptr) {
    // Note: m % n & = m & (n - 1) if n is a power of two.
    // Alignment requirements are always a power of two.

    return reinterpret_cast<uintptr_t>(ptr) & (alignOf - 1);
}

inline uintptr_t oAlignmentAdjustment(sizet alignOf, const void* const ptr) {
    uintptr_t offset = oAlignmentOffset(alignOf, ptr);

    // If the address is already aligned we don't need any adjustment.

    if (offset == 0)
        return 0;

    return alignOf - offset;
}