#include "STLpch.h"
#include "Allocators/StackAllocator.h"


struct MemoryBlockHeader
{
	U32 size{ 0 };
};

StackMemoryPool::StackMemoryPool(PtrSize size, U32 alignbits):memSize{size}, alignmentBits{alignbits}
{
	assert(size > 0);
	memory = static_cast<U8*>(::_aligned_malloc(memSize, alignmentBits));

	if (memory != nullptr)
	{
		top.store(memory);
	}
	else
	{
		fmt::print("aligned_malloc() failed!");
	}

}

StackMemoryPool::~StackMemoryPool()
{
	if (memory != nullptr)
	{
		::_aligned_free(memory);
	}
}


StackMemoryPool& StackMemoryPool::operator=(StackMemoryPool&& other) noexcept
{
	if(memory!=nullptr)
	{
		::_aligned_free(memory);
	}

	memory = other.memory;
	memSize = other.memSize;
	top.store(other.top.load());

	other.memory = nullptr;
	other.memSize = 0;
	other.top=nullptr;

	return *this;
}


PtrSize StackMemoryPool::getAllocatedSize() const noexcept
{
	return top.load()-memory;
}

void* StackMemoryPool::allocate(PtrSize size)
{
	assert(memory != nullptr);
	PtrSize realsize = calcAlignSize(size + sizeof(MemoryBlockHeader));

	/*check if the size is bigger to fit in 32 bits*/
	assert(realsize < std::numeric_limits<U32>::max());

	U8* out = top.fetch_add(size);

	if (out + size <= memory + memSize)
	{
		((MemoryBlockHeader*)out)->size = static_cast<U32>(size);

		out += sizeof(MemoryBlockHeader);
	}
	else
	{
		/*error!*/
		out = nullptr;
		fmt::print("Not enough memory size!");
	}

	return static_cast<void*>(out);
}

bool StackMemoryPool::free(void* p) noexcept
{
	return false;
}

void StackMemoryPool::reset() noexcept
{
}



const PtrSize StackMemoryPool::calcAlignSize(PtrSize size) const noexcept
{
	return size;
}
