#pragma once
#include "STLContpch.h"
#include "ContainerUtilities.hpp"

inline void SetMultiSet_Test()
{
	fmt::print("\n---------------------Set-MultiSet Test------------------------------------\n\n");

	std::set<int> set1 = { 1, 5, 3, 6, 7, 28 };
	printCont(set1);

	std::set<int, std::greater<int>> set2{ set1.cbegin(), set1.cend() };
	printCont(set2);

	std::cout<<*(set1.lower_bound(5))<<'\n';
	std::cout << *(set1.upper_bound(5)) << '\n';

	auto&& [first, second] = set1.equal_range(5);
	std::cout << *first << ", " << *second << '\n';
	std::cout << std::boolalpha;
	std::set<float>set3 = { 1.2f, 3.4f, 5.6f };
	printCont(set3);
	
	/* if loop uses initialization and check incl in c++17*/
	if(auto&& [pos, success] = set3.insert(3.3f); success)
	{
		printCont(set3);
		fmt::print(" set3 insertion {}\n", success);
		fmt::print("the {0} inserted at position {1} \n", *pos, std::distance(set3.begin(), pos)+1);
	}
	else
	{
		printCont(set3);
		fmt::print(" set3 insertion {}\n", success);
	}

	auto success = set3.erase(3.4f);
	if(success) printCont(set3);

	std::multiset<int> mset4{ set1.begin(), set1.end() };
	printCont(mset4);

	auto newpos=mset4.insert(5);
	printCont(mset4);
	fmt::print("the {0} inserted in mset4 at position {1} \n", *newpos, std::distance(mset4.begin(), newpos) + 1);

}