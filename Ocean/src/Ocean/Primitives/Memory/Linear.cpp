#include "Linear.hpp"

#include "Ocean/Core/Assert.hpp"

#include "Ocean/Primitives/Memory/Common.hpp"

void LinearAllocator::Init(sizet size) {
	this->p_Memory = static_cast<u8*>(malloc(size));
	this->m_TotalSize = size;
	this->m_AllocatedSize = 0;
}

void LinearAllocator::Shutdown() {
	free(this->p_Memory);
}

void* LinearAllocator::Allocate(sizet size, sizet alignment) {
	OASSERT(size > 0);

	const sizet newStart = oAlignmentAdjustment(alignment, this->p_Memory + this->m_AllocatedSize);

	OASSERT(newStart < this->m_TotalSize);

	const sizet newSize = newStart + size;

	if (newSize > this->m_TotalSize) {
		OASSERTM(false, "MEMORY OVERFLOW |: Linear Allocator");
		return nullptr;
	}

#ifdef OC_DETAILED_ALLOCATIONS

	s_Stats.Add(size);

#endif

	this->m_AllocatedSize = newSize;
	return this->p_Memory + newStart;
}

void LinearAllocator::Deallocate(OC_UNUSED void* ptr) {
	oprint("Linear Allocator Deallocate called when it does not do anything!");
	// This allocator does not allocate on a per-pointer base.
}

void LinearAllocator::Clear() {
#ifdef OC_DETAILED_ALLOCATIONS

	s_Stats.Remove(this->m_AllocatedSize);

#endif

	this->m_AllocatedSize = 0;
}
