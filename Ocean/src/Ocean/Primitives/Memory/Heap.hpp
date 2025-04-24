/**
 * @file Heap.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Primitives/Memory/Allocator.hpp"

/**
 * @brief The heap allocator allocates memory in as requested blocks.
 */
class HeapAllocator : public Allocator {
public:
	~HeapAllocator() override;

	/**
	 * @brief Initializes the HeapAllocator to store a maximum of the given size.
	 * 
	 * @param size The amount of memory to store in bytes.
	 */
	void Init(sizet size);
	/**
	 * @brief Clears all of the memory and shuts down the HeapAllocator.
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

private:
	void* p_Handle = nullptr; /** @brief The tlsf handle for the memory pool. */
	void* p_Memory = nullptr; /** @brief The base memory pointer of the heap. */

	sizet m_TotalSize = 0; /** @brief The total size of the heap. */
	sizet m_AllocatedSize = 0; /** @brief The amount of memory that is allocated in the heap. */

};	// HeapAllocator
