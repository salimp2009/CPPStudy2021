#pragma once
#include "RangesPCH.hpp"

template<typename Func, std::ranges::input_range Seq>
auto filter(Func func, Seq seq)
{
	using value_type = typename Seq::value_type;

	std::vector<value_type> result{};
	

	for (auto i : seq | std::views::filter(func))
	{
		result.emplace_back(i);
	}

	return result;
}

inline void FilterRanges_PythonStyle()
{
	std::printf("\n---FilterRanges_PythonStyle---\n");

	std::vector<int> myInts(50);
	std::iota(myInts.begin(), myInts.end(), 1);

	auto result = filter([](auto elem) { return elem % 3 == 0; }, myInts);
	for (auto elem : result)
	{
		fmt::print("{} ", elem);
	}
	puts("\n");

	std::vector<std::string> myStrings = { "Only", "for", "testing", "stuff" };

	auto result2 = filter([](std::string_view elem) {return std::isupper(elem[0]); }, myStrings);

	fmt::print("{}",fmt::join(result2, " "));
	puts("\n");

}