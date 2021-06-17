#pragma once
#include "RangesPCH.hpp"


inline void RangeExample01()
{
	std::printf("\n---RangeExample01---\n");

	std::vector numbers = { 1,2,3,4,5,6};

	auto result = numbers | std::views::filter([](int n) { return n % 2 == 0; })
						  | std::views::transform([](int n) { return n * 2; });

	for (auto v : result)
	{
		fmt::print("{} ", v);
	}
	puts("\n");
}
