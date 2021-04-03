#pragma once

#include "STLContpch.h"


inline void MapMultiMap_Test()
{
	fmt::print("\n---------------------Map-MultiMap Test------------------------------------\n\n");

	std::map<int, std::string, std::greater<int>> coll1 = { {51,"Salim"}, {68, "Sema"} };
	printMCont(coll1);

	std::cout << coll1[51] << '\n';
	 
	std::map<int, std::string, std::greater<int>>coll2(coll1.begin(), coll1.end());
	printMCont(coll2);
	coll2[68] = "Semos";

	std::cout << std::boolalpha;
	/* equality checks both size of map and the values match or not; and the ordering needs to match*/
	std::cout << (coll2 == coll1) << '\n';

	for (auto& elem : coll2)
	{
		if (elem.second == "Salim")
		{
			coll2.erase(elem.first);
			/*if you dont use break then program will try iterate the deleted iterator and give runtime error*/
			break;
		}
	}

	printMCont(coll2);

	/*Alternative way to above code; iterate only if the value does not match*/
	for (auto pos = coll2.begin(); pos != coll2.end();)
	{
		if (pos->second == "Semos")
		{
			/** erase return the next pos so when we delete the current iterator program will increment over the next valid iterator
				or use pos++ inside the erase
			*/
			pos=coll2.erase(pos);
		}
		else
		{
			++pos;
		}
	}
	printMCont(coll2);

	coll2.emplace(50, "Didem");
	printMCont(coll2);

}
