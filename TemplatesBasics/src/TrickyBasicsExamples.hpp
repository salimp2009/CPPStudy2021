#pragma once

#include "Templpch.h"

template<class T>
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

template<typename T, std::size_t N, std::size_t M>
constexpr bool lessArray(T(&a)[N], T(&b)[M])
{
	for (auto i = 0; i<N && i<M; ++i)
	{
		if (a[i] < b[i]) return true;
		if (b[i] < a[i]) return false;
	}

	return N < M;
}

inline void TrickyBasics_Arrays()
{
	std::printf("\n------------TrickyBasics Arrays------------\n");

	int x[] = { 1,2,3,4,5,6 };
	int y[] = { 1,2,3,4};
	fmt::print("less array: {0}\n", lessArray(x, y));

	char s1[] = "salim";
	char s2[] = "didem";
	fmt::print("less array: {0}\n", lessArray("didem", "salim"));
	fmt::print("less array: {0}\n", lessArray(s2, s1));

}