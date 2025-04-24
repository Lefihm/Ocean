/**
 * @file Malloc.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Primitives/Memory/Allocator.hpp"

/**
 * @brief Allocates memory using classic C-style malloc and free.
 */
class MallocAllocator : public Allocator {
public:
	/**
	 * @copydoc Allocator::Allocate()
	 */
	virtual void* Allocate(sizet size, sizet alignment) override;

	/**
	 * @copydoc Allocator::Deallocate() 
	 */
	virtual void Deallocate(void* ptr) override;

};	// MallocAllocator
