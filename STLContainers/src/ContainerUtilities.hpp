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



