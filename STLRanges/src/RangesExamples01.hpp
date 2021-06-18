#pragma once
#include "RangesPCH.hpp"


inline void RangeExample01()
{
	std::printf("\n---RangeExample01---\n");

	const std::vector<int> numbers = { 1,2,3,4,5,6};

	auto result = numbers | std::views::filter([](int n) { return n % 2 == 0; })
						  | std::views::transform([](int n) { return n * 2; });
						  //| std::ranges::views::split(2);

	for (auto v : result)
	{
		fmt::print("{} ", v);
		
	}
	puts("\n");

	std::vector<int> vec2 = { -3,5,0,7,-4 };
	std::ranges::sort(vec2);
	for (const auto elem : vec2)
	{
		fmt::print("{} ", elem);
	}
	puts("\n");
}
