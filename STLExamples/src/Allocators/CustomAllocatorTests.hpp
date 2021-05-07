#pragma once

#include "MyAlloc.hpp"
#include "StackAllocator.h"


inline void CustomAllocator_Basics()
{
	fmt::print("\n---------------Custom Allocator Basics--------------------------\n");

	

	std::vector<int, MyAlloc<int>> vec1{ 1,2,3,4,5 };

	//std::cout << allocCount << '\n';

	printCont(vec1);

	vec1.insert(vec1.end(), { 7, 8, 9, 10, 12, 13, 4, 5, 788, 99, 80 });

	printCont(vec1);

	Vec<int> vec2{ vec1 };
	printCont(vec2);
}
