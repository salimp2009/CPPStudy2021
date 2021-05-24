#pragma once

#include "Templpch.h"
#include "ArrayOverloads.hpp"

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
	std::printf("\n--TrickyBasics Arrays--\n");

	int x[] = { 1,2,3,4,5,6 };
	int y[] = { 1,2,3,4};
	fmt::print("less array: {0}\n", lessArray(x, y));

	char s1[] = "salim";
	char s2[] = "didem";
	fmt::print("less array: {0}\n", lessArray("didem", "salim"));
	fmt::print("less array: {0}\n", lessArray(s2, s1));

}

template<typename T1,  typename T2, typename T3>
void testArrays(int a1[7], int a2[], /*pointer by language rules*/
	int(&a3)[42],		 /*reference to array of known bounds*/
	int(&x0)[],			 /*reference to array of unknow bounds*/
	T1 x1,				 /*passing by value decays*/
	T2& x2, T3&& x3)	 /*passing by reference*/

{
	MyClass<decltype(a1)>::print();		/*goes T* overloaded version*/
	MyClass<decltype(a2)>::print();		/*goes T* overloaded version*/
	MyClass<decltype(a3)>::print();		/*goes T(&a)[n]; reference to array with known bounds*/
	MyClass<decltype(x0)>::print();		/*goes T(&a)[]; reference to array with unknown bounds*/
	MyClass<decltype(x1)>::print();
	MyClass<decltype(x2)>::print();
	MyClass<decltype(x3)>::print();
}


inline void ArrayOverloads_Test()
{
	std::printf("\n--Array Overloads--\n");
	int a[42] = { 0 };
	MyClass<decltype(a)>::print(); //goes to T[SZ]

	extern int x[];
	MyClass<decltype(x)>::print(); // goes to T[]

	testArrays(a, a, a, x, x, x, x);
}

int x[] = { 0,8,15 };