#pragma once
#include "STLContpch.h"

/* cause some overload problems; better to use this for specific class to overload that class*/


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& cont) 
{
	for (const auto& elem : cont)
	{
		os << elem << " ";
	}
	return os;
}


template<typename Cont>
constexpr void printCont(Cont& cont)
{
	if (cont.empty()) return;

	for (auto&& elem : cont)
	{
		fmt::print("{} ", elem);
	}
	std::cout << '\n';
}


template<typename InputIterator, typename Tval>
constexpr InputIterator find_before(InputIterator first, InputIterator last, Tval&& val)
{
	if (first == last)
	{
		return first;
	}

	InputIterator next{ first };
	++next;

	while (next != last && *next != val)
	{
		++next;
		++first;
	}

	return first;
}

template<class InputIterator, class Tpred>
constexpr InputIterator find_before_if(InputIterator first, const InputIterator last, Tpred&& pred)
{
	if (first == last)
	{
		return first;
	}

	InputIterator next{ first };
	++next;

	while (next != last && !pred(std::forward<decltype(*next)>(*next)))
	{
		++next;
		++first;
	}

	return first;
}



