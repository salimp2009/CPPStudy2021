#pragma once
#include "RangesPCH.hpp"

struct MyInt
{
	int value;
	explicit MyInt(int val) : value{ val } {}
	bool  operator==(const MyInt&) const = default;
	auto operator<=>(const MyInt& rhs) const { return value <=> rhs.value; }
};

struct MyDouble
{
	double value;
	explicit constexpr MyDouble(double val) : value{ val } {}
	auto  operator<=>(const MyDouble&) const = default;
};

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


}
