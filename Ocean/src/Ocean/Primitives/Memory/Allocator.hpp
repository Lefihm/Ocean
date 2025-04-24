/**
 * @file Allocator.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Types/Integers.hpp"

/**
 * @brief The base class of a memory allocator.
 */
class Allocator {
public:
	virtual ~Allocator() = default;

	/**
	 * @brief Allocates memory of the given size and alignment.
	 * 
	 * @param size The size in bytes to allocate.
	 * @param alignment The alignment of the allocation.
	 * @return void* 
	 */
	virtual void* Allocate(sizet size, sizet alignment = alignof(max_align_t)) = 0;

	/**
	 * @brief Deallocates memory at the given pointer.
	 * 
	 * @param ptr The pointer to the memory to deallocate.
	 */
	virtual void Deallocate(void* ptr) = 0;

};	// Allocator
