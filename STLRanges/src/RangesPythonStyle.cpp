#include "RangesPCH.hpp"
#include "RangesFilterPythonStyle.hpp"


void FilterRanges_PythonStyle()
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

	fmt::print("{}", fmt::join(result2, " "));
	puts("\n");

}

void TransforMapRanges_PythonStyle()
{
	std::printf("\n---TransforMapRanges_PythonStyle---\n");

	std::list<int> myInts{ 1,2,3,4,5,6,7,8,9,10 };
	auto result = map([](auto&& elem) { return elem * elem; }, myInts );

	puts("\noriginal list: ");
	fmt::print("{}", fmt::join(myInts, " "));
	puts("\n");

	for (auto i : result)
	{
		fmt::print("{} ", i);
	}
	puts("\n");


	std::vector<std::string> myStrings{ "Only", "for", "testing", "purposes" };
	auto result2 = map([](auto&& elem) { return std::make_pair(elem.size(), elem); }, myStrings);


	for (auto i : result2)
	{
		fmt::print("size: {}, text: {}\n", i.first, i.second);
	}
	puts("\n");

}
