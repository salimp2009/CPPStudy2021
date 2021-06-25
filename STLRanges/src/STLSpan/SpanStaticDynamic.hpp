#pragma once
#include "RangesPCH.hpp"

inline void DynamicExtent_Span()
{
	std::printf("\n---DynamicExtent_Span---\n");

	auto printCont = [](std::span<int> container)
	{
		fmt::print("container size : {}\n", container.size());
		fmt::print("{}\n", fmt::join(container, ", "));
	};

	int arr[] = { 1,2,3,4,5 };
	printCont(arr);

	std::vector vec1{ 1,2,4,5 };
	printCont(vec1);

	std::array arr2{ 1,2,3, };
	printCont(arr2);

}

inline void StaticDynamicExtent_Span()
{
	std::printf("\n---StaticDynamicExtent_Span---\n");
	auto printCont = [](std::span<int> container)
	{
		fmt::print("container size : {}\n", container.size());
		fmt::print("{}\n", fmt::join(container, ", "));
	};

	std::vector<int> myVec1{ 1,2,3,4,5 };
	std::vector myVec2{ 1,2,3,4 };

	std::span<int>	  dynamicSpan{ myVec1 };
	std::span<int, 4> staticSpan{ myVec2 };

	std::span pointerSpan{ myVec2.data(), myVec2.size() };

	printCont(dynamicSpan);
	printCont(staticSpan);
	printCont(pointerSpan);

	fmt::print("size of dynamic span : {}\n", sizeof(dynamicSpan));
	fmt::print("size of static span : {}\n", sizeof(staticSpan));
	fmt::print("size of pointer span : {}\n", sizeof(pointerSpan));

}
