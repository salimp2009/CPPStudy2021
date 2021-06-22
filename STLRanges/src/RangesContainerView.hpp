#pragma once
#include "RangesPCH.hpp"

template<std::ranges::input_range Range>
requires std::ranges::view<Range>
class ContainerView :public std::ranges::view_interface<ContainerView<Range>>
{
private:
	Range mRange{};
	std::ranges::iterator_t<Range> mbegin{ std::begin(mRange) };
	std::ranges::iterator_t<Range> mend{std::end(mRange)};


public:
	// this is needed to satisfy the view concept; https://en.cppreference.com/w/cpp/ranges/view_interface
	ContainerView() = default;
	
	constexpr ContainerView(Range r):mRange{std::move(r)}, mbegin{std::begin(r)}, mend{std::end(r)} { }

	constexpr auto begin() const { return mbegin; }
	constexpr auto end()   const { return mend; }
};

// Deduction Guide to make it easier for user
template<typename Range>
ContainerView(Range&& range)->ContainerView<std::ranges::views::all_t<Range>>;

inline void ContainerView_CustomView()
{
	std::printf("\n---ContainerView_CustomView---\n");

	std::vector<int> vec1 = { 1,2,3,4,5,6,7,8,9 };
	auto myContView = ContainerView(vec1);
	puts("User defined Container View: \n");
	for (auto elem : myContView)
	{
		std::printf("%d ", elem);
	}
	puts("\n");

	puts("Container View Reverse: \n");
	for (auto elem : std::views::reverse(myContView))
	{
		std::printf("%d ", elem);
	}
	puts("\n");

	puts("Container View first 4 elements: \n");
	for (auto elem : std::views::take(myContView, 4))
	{
		std::printf("%d ", elem);
	}
	puts("\n");
}