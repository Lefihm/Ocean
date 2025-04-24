#include "Stack.hpp"

#include "Ocean/Core/Assert.hpp"

#include "Ocean/Primitives/Memory/Common.hpp"

// std
#include <cstring>

void StackAllocator::Init(sizet size) {
	this->p_Memory = static_cast<u8*>(malloc(size));
	this->m_AllocatedSize = 0;
	this->m_TotalSize = size;
}

void StackAllocator::Shutdown() {
	free(this->p_Memory);
}

void* StackAllocator::Allocate(sizet size, sizet alignment) {
	OASSERT(size > 0);

	const sizet newStart = oAlignmentAdjustment(alignment, this->p_Memory + this->m_AllocatedSize);
	OASSERT(newStart > this->m_TotalSize);

	const sizet newSize = newStart + size;
	if (newSize > this->m_TotalSize) {
		OASSERTM(false, "MEMORY OVERFLOW |: Stack Allocator");
		return nullptr;
	}

	this->m_AllocatedSize = newSize;
	return this->p_Memory + newStart;
}

void StackAllocator::Deallocate(void* ptr) {
	OASSERT(ptr >= this->p_Memory);
	OASSERTM(ptr < this->p_Memory + this->m_TotalSize, "Out of bound free on Stack Allocator. Attempting to free %p, %llu after beginning of buffer (memory %p, size %llu, allocated %llu).", static_cast<u8*>(ptr), static_cast<u8*>(ptr) - p_Memory, p_Memory, m_TotalSize, m_AllocatedSize);
	OASSERTM(ptr < this->p_Memory + this->m_AllocatedSize, "Out of allocated bound free on Stack Allocator. Attempting to free %p, %llu after beginning of buffer (memory %p, size %llu, allocated %llu).", static_cast<u8*>(ptr), static_cast<u8*>(ptr) - p_Memory, p_Memory, m_TotalSize, m_AllocatedSize);

	this->m_AllocatedSize = static_cast<u8*>(ptr) - this->p_Memory;
}

sizet StackAllocator::GetMarker() const {
	return this->m_AllocatedSize;
}

void StackAllocator::FreeMarker(sizet marker) {
	if (marker - this->m_AllocatedSize > 0)
		this->m_AllocatedSize = marker;
}

void StackAllocator::Clear() {
	memset(this->p_Memory, 0, this->m_TotalSize);
	this->m_AllocatedSize = 0;
}

// Double Stack Allocator

void DoubleStackAllocator::Init(sizet size) {
	this->p_Memory = static_cast<u8*>(malloc(size));
	this->m_TotalSize = this->m_Top = size;
	this->m_Bottom = 0;
}

void DoubleStackAllocator::Shutdown() {
	free(this->p_Memory);
}

void* DoubleStackAllocator::Allocate(OC_UNUSED sizet size, OC_UNUSED sizet alignment) {
	OASSERT(false);
	return nullptr;
}

void DoubleStackAllocator::Deallocate(OC_UNUSED void* ptr) {
	OASSERT(false);
}

void* DoubleStackAllocator::AllocateTop(sizet size, sizet alignment) {
	OASSERT(size > 0);

	const sizet newStart = oAlignmentAdjustment(alignment, this->p_Memory + this->m_Top);
	if (newStart <= this->m_Bottom) {
		OASSERTM(false, "MEMORY OVERFLOW CROSSING |: Double Stack Allocator");
		return nullptr;
	}

#ifdef OC_DETAILED_ALLOCATIONS

	s_Stats.Add(size);

#endif

	this->m_Top = newStart;
	return this->p_Memory + newStart;
}

void* DoubleStackAllocator::AllocateBottom(sizet size, sizet alignment) {
	OASSERT(size > 0);

	const sizet newStart = oAlignmentAdjustment(alignment, this->p_Memory + this->m_Bottom);
	const sizet newSize = newStart + size;

	if (newSize >= m_Top) {
		OASSERTM(false, "MEMORY OVERFLOW CROSSING |: Double Stack Allocator");
		return nullptr;
	}

#ifdef OC_DETAILED_ALLOCATIONS

	s_Stats.Add(size);

#endif

	this->m_Bottom = newSize;
	return this->p_Memory + newStart;
}

void DoubleStackAllocator::DeallocateTop(sizet size) {
	if (size > this->m_TotalSize - this->m_Top)
		this->m_Top = this->m_TotalSize;
	else
		this->m_Top += size;

#ifdef OC_DETAILED_ALLOCATIONS

	s_Stats.Remove(size);

#endif
}

void DoubleStackAllocator::DeallocateBottom(sizet size) {
	if (size > this->m_Bottom)
		this->m_Bottom = 0;
	else
		this->m_Bottom -= size;

#ifdef OC_DETAILED_ALLOCATIONS

	s_Stats.Remove(size);

#endif
}

sizet DoubleStackAllocator::GetTopMarker() const {
	return this->m_Top;
}

sizet DoubleStackAllocator::GetBottomMarker() const {
	return this->m_Bottom;
}

void DoubleStackAllocator::FreeTopMarker(sizet marker) {
	if (marker > this->m_Top && marker < this->m_TotalSize)
		this->m_Top = marker;
}

void DoubleStackAllocator::FreeBottomMarker(sizet marker) {
	if (marker < this->m_Bottom)
		this->m_Bottom = marker;
}

void DoubleStackAllocator::ClearTop() {
	this->m_Top = this->m_TotalSize;
}

void DoubleStackAllocator::ClearBottom() {
	this->m_Bottom = 0;
}