/**
 * @file Stack.hpp
 * @brief 
 * 
 * @author Evan F.
 * 
 * @copyright Copyright 2025 Lefihm Interactive
 */
#pragma once

#include "Ocean/Primitives/Memory/Allocator.hpp"

/**
 * @brief An allocator that treats the memory as a stack, that can be pushed to and popped from.
 */
class StackAllocator : public Allocator {
public:
	/**
	 * @brief Initializes the StackAllocator to store a maximum of the given size.
	 * 
	 * @param size The amount of memory to store in bytes.
	 */
	void Init(sizet size);
	/**
	 * @brief Clears all of the memory and shuts down the StackAllocator.
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
	 * @brief Get the marker of the stack.
	 * 
	 * @return sizet
	 */
	sizet GetMarker() const;
	/**
	 * @brief Free's the 
	 * 
	 * @param marker 
	 */
	void FreeMarker(sizet marker);

	/**
	 * @brief Clear's the memory and reset's the marker.
	 */
	void Clear();

private:
	u8* p_Memory = nullptr; /** @brief The base memory pointer of the allocator. */

	sizet m_TotalSize = 0; /** @brief The total size of the allocator. */
	sizet m_AllocatedSize = 0; /** @brief The amount of memory that is allocated in the allocator. */

};	// StackAllocator



/**
 * @brief An allocator that treats the memory as a double sided stack, that can be pushed and popped from both ends.
 */
class DoubleStackAllocator : public Allocator {
public:
	/**
	 * @brief Initializes the DoubleStackAllocator to store a maximum of the given size.
	 * 
	 * @param size The amount of memory to store in bytes.
	 */
	void Init(sizet size);
	/**
	 * @brief Clears all of the memory and shuts down the DoubleStackAllocator.
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
	 * @brief Allocates memory at the top of the stack.
	 * 
	 * @param size The size of the memory to allocate.
	 * @param alignment The alignment of the memory.
	 *
	 * @return void* 
	 */
	void* AllocateTop(sizet size, sizet alignment);
	/**
	 * @brief Allocates memory at the bottom of the stack.
	 * 
	 * @param size The size of the memory to allocate.
	 * @param alignment The alignment of the memory.
	 *
	 * @return void* 
	 */
	void* AllocateBottom(sizet size, sizet alignment);

	/**
	 * @brief Deallocates memory at the top of the stack.
	 * 
	 * @param size The amount of memory to deallocate.
	 */
	void DeallocateTop(sizet size);
	/**
	 * @brief Deallocates memory from the bottom of the stack.
	 * 
	 * @param size The amount of memory to deallocate.
	 */
	void DeallocateBottom(sizet size);

	/**
	 * @brief Get the marker at the top of the stack.
	 * 
	 * @return sizet 
	 */
	sizet GetTopMarker() const;
	/**
	 * @brief Get the marker at the bottom of the stack.
	 * 
	 * @return sizet 
	 */
	sizet GetBottomMarker() const;

	/**
	 * @brief Reset's memory from the top marker to the given marker.
	 * 
	 * @param marker The marker index to free to.
	 */
	void FreeTopMarker(sizet marker);
	/**
	 * @brief Reset's memory from the bottom marker to the given marker.
	 * 
	 * @param marker The marker index to free to.
	 */
	void FreeBottomMarker(sizet marker);

	/**
	 * @brief Clear's the top of the stack, i.e. reset's the top marker to the top of the stack.
	 */
	void ClearTop();
	/**
	 * @brief Clear's the bottom of the stack, i.e. reset's the bottom marker to the bottom of the stack.
	 */
	void ClearBottom();

private:
	u8* p_Memory = nullptr; /** @brief The base memory pointer of the allocator. */

	sizet m_TotalSize = 0; /** @brief The total size of the allocator. */
	sizet m_Top = 0; /** @brief The size distance from the top of the memory block. */
	sizet m_Bottom = 0; /** @brief The size distance from the bottom of the memory block. */

};	// DoubleStackAllocator
