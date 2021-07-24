#pragma once
#include "RangesPCH.hpp"
#include "ThreewayComparisionUtils.hpp"
#include "ThreewayComparisionUtils2.hpp"

inline void ThreeWayComparision_Test1()
{
	std::printf("\n- ThreeWayComparision_Test1-\n");

	constexpr auto isLessThan = []<typename T>(T && lhs, T &&rhs) constexpr
	{
		return lhs < rhs;
	};

	MyInt int1{ 2017 };
	MyInt int2{ 2021 };

	constexpr MyDouble db1{ 20.25 };
	constexpr MyDouble db2{ 40.25 };

	fmt::print("2017 < 2021: {}\n", isLessThan(int1, int2));
	fmt::print("2017 == 2021: {}\n", (int1==int2)); // does not compile if operator == is not defined!!!
	
	// spaceship operator is constexpr and MyDouble has also constepxr constructor so if the values are known
	// at compile time and then check is also compile time as above
	static_assert(db1 != db2);
	
	fmt::print("20.25== 40.25: {}\n", (db1==db2)); 

	VectorPointer vecptr1{ new std::vector<int>() };
	VectorPointer vecptr2{ new std::vector<int>() };

	fmt::print("vecptr1==vecptr2: {}\n", (vecptr1 == vecptr2));

}

inline void StringComparision_Test1()
{
	String str1{ "Hello" };
	String str2{ "C++20" };
	String str3{ "Hello" };
	String str4{ "hello" };
	String str5{ "HELLO" };

	fmt::print("Hello == Hello: {}\n", (str1 == str3));
	fmt::print("Hello == hello: {}\n", (str1 == str4));
	fmt::print("Hello < C++20: {}\n", (str1 < str2));
	fmt::print("Hello > C++20: {}\n", (str1 > str2));
	fmt::print("Hello == HELLO: {}\n", (str1 == str5));

	char a = 'H';
	char b = 'C';

	fmt::print("H > C: {}\n", (a > b));
	fmt::print("H < C: {}\n", (a < b));

}

inline void SpaceShipOperator_Test1()
{
	std::printf("\n-SpaceShipOperator_Test1-\n");

	int a{ 2012 };
	int b{ 2021 };
	auto result = a <=> b;
	fmt::print("result : {}\n", (result < 0 ? "a<b" : (result == 0 ? "a==b" : "a>b")));
	fmt::print("is_eq(a<=>b) : {}\n", std::is_eq(a<=>b));

	std::string s1{ "2014" };
	std::string s2{ "2011" };

	auto result2 = s1 <=> s2;
	fmt::print("result2 (2014<=>2011) : {}\n", (result2 < 0 ? "s1<s2" : (result2 == 0 ? "s1==s2" : "s1>s2")));

	std::vector v1{ 1,2,3 };
	std::vector v2{ 1,2,3 };
	auto result3 = v1 <=> v2;

	fmt::print("result3 (v1{{ 1,2,3 }}<=>v2{{ 1,2,3 }}) : {}\n", (result3 < 0 ? "v1<v2" : (result3 == 0 ? "v1==v2" : "v1>v2")));
}

inline void AddressSort()
{
	std::printf("\n-AddressSort-\n");

	Address address1{ "Istanbul", "Seyrantepe", 34710 };
	Address address2{ "Istanbul", "Kadikoy", 35710 };
	auto result = address1 <=> address2;
	fmt::print("address1 > address2 (expected:true) : {}\n", (result < 0 ? "address1<address2" : (result == 0 ? "address1==address2" : "address1>address2")));
}

inline void BinaryCodedDigit()
{
	std::printf("\n-BinaryCodedDigit-\n");

	constexpr BCD binarycodeDigit1{ 10, 1 };
	constexpr BCD binarcodeDigit2{ 0, 2 };
	constexpr int value = binarycodeDigit1;
	static_assert(value == 0);
	static_assert(binarycodeDigit1 != binarcodeDigit2);
	static_assert(value == binarycodeDigit1);
	static_assert(value == binarcodeDigit2);
}

inline void LegacyWrapCompare()
{
	std::printf("\n-LegacyWrapCompare()-\n");

	LegacyWrap lWrap1{ 2,3 };
	LegacyWrap lWrap2{ 2,3 };
	LegacyWrap lWrap3{ 4,5 };

	assert(lWrap1== lWrap2);
	assert(lWrap3 > lWrap2);
	assert(!(lWrap3 < lWrap2));
}





