#pragma once
#include "RangesPCH.hpp"

inline void StaticDynamicExtent_Span()
{
	std::printf("\n---StaticDynamicExtent_Span---\n");

	auto printCont = [](std::span<int> container)
	{
		fmt::print("container size : {}\n", container.size());
		fmt::print("{}\n", fmt::join(container, ", "));
	};

	int arr[] = { 1,2,3,4,5 };
	printCont(arr);

	std::vector vec1{ 1,2,3,4,5 };
	printCont(vec1);

	std::array arr2{ 1,2,3,4,5 };
	printCont(arr2);

}

