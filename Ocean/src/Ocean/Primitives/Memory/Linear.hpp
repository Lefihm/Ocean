/**
 * @file Linear.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Primitives/Memory/Allocator.hpp"

/**
 * @brief An allocator that treat's memory as an array, memory cannot be deallocate memory without clearing the array.
 */
class LinearAllocator : public Allocator {
public:
	/**
	 * @brief Initializes the LinearAllocator to store a maximum of the given size.
	 * 
	 * @param size The amount of memory to store in bytes.
	 */
	void Init(sizet size);
	/**
	 * @brief Clears all of the memory and shuts down the LinearAllocator.
	 */
	void Shutdown();

	/**
	 * @copydoc Allocator::Allocate()
	 */
	virtual void* Allocate(sizet size, sizet alignment) override;

	/**
	 * @copydoc Allocator::Deallocate() 
	 */
	virtual void Deallocate(void* ptr) override;

	/**
	 * @brief Clear's the allocator's memory.
	 */
	void Clear();

private:
	u8* p_Memory = nullptr; /** @brief The base memory pointer of the allocator. */

	sizet m_TotalSize = 0; /** @brief The total size of the allocator. */
	sizet m_AllocatedSize = 0; /** @brief The amount of memory that is allocated in the allocator. */

};	// LinearAllocator
