#pragma once

#include "Templpch.h"

template<typename T>
void printColl(const T& coll)
{
	typename T::const_iterator pos;
	typename T::const_iterator end(coll.end());

	for (pos = coll.begin(); pos != end; ++pos)
	{
		fmt::print("{0} \n", *pos);
	}
}


inline void TrickyBasics01()
{
	std::printf("\n------------TrickyBasics01------------\n");

	std::vector<int> vec1 = { 1,2,3,4 };
	printColl(vec1);
}