#pragma once
#include "Allocators/StackMemoryPool.h"

/* TODO ; check if the type of the stack allocator "T" needs to atomic constraint to use with custom types!!!*/
template<typename T>
concept atomicTypes = !std::is_polymorphic_v<T> && std::is_trivially_copy_constructible_v<T> && std::is_trivial_v<T>;


template<typename T, bool deallocationFlag=false, U32 alignmentBits=16>
class StackAllocator
{






};
