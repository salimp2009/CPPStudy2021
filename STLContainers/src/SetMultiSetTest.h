#pragma once
#include "STLContpch.h"
#include "ContainerUtilities.hpp"

inline void SetMultiSet_Test()
{
	fmt::print("\n---------------------Set-MultiSet Test------------------------------------\n\n");

	std::set<int> set1 = { 1, 5, 3, 6, 7, 28 };
	printCont(set1);

	std::set<int, std::greater<int>> set2 = { 1, 5, 3,28 };
	printCont(set2);

	std::cout<<*(set1.lower_bound(5))<<'\n';
	std::cout << *(set1.upper_bound(5)) << '\n';

	auto&& [first, second] = set1.equal_range(5);
	std::cout << *first << ", " << *second << '\n';

}