#pragma once
#include "RangesPCH.hpp"
#include "ThreewayComparisionUtils.hpp"

inline void ThreeWayComparision_Test1()
{
	std::printf("\n- ThreeWayComparision_Test1-\n");

	constexpr auto isLessThan = []<typename T>(T && lhs, T &&rhs) constexpr
	{
		return lhs < rhs;
	};

	MyInt int1{ 2017 };
	MyInt int2{ 2021 };

	MyDouble db1{ 20.25 };
	MyDouble db2{ 40.25 };

	fmt::print("2017 < 2021: {}\n", isLessThan(int1, int2));
	fmt::print("2017 == 2021: {}\n", (int1==int2)); // does not compile if operator == is not defined!!!
	
	
	fmt::print("20.25== 40.25: {}\n", (db1==db2)); 

	VectorPointer vecptr1{ new std::vector<int>() };
	VectorPointer vecptr2{ new std::vector<int>() };

	fmt::print("vecptr1==vecptr2: {}\n", (vecptr1 == vecptr2));

	String str1{ "Hello" };
	String str2{ "C++20" };
	String str3{ "Hello" };
	String str4{ "hello" };

	fmt::print("Hello == Hello: {}\n", (str1 == str3));
	fmt::print("Hello == hello: {}\n", (str1 == str4));
	fmt::print("Hello < C++20: {}\n", (str1 < str2));
	fmt::print("Hello > C++20: {}\n", (str1 > str2));

	char a = 'H';
	char b = 'C';

	fmt::print("H > C: {}\n", (a > b));
	fmt::print("H < C: {}\n", (a < b));

}
