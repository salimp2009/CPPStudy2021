#pragma once
#include "ConceptUtilities.hpp"
#include "ConceptUtils02.hpp"


inline void greatCommonDiv_Concepts()
{
	std::printf("\n---great Common Div Concepts---\n");

	fmt::print("greaterCommonDivisor(100, 10): {}\n", greaterCommonDivisor(100, 10));
	fmt::print("greaterCommonDivisor1(5, 1): {}\n", greaterCommonDivisor1(5, 1));
	fmt::print("greaterCommonDivisor2(5, 1): {}\n", greaterCommonDivisor2(5, 1));
	fmt::print("greaterCommonDivisor3(5, 1): {}\n", greaterCommonDivisor3(5, 1));
	fmt::print("greaterCommonDivisor3(1, 5): {}\n", greaterCommonDivisor3(1, 5));

	/* before concepts using std::enable_if_t*/
	std::printf("addValues before concepts: %d \n", addValues(1, 2, 3, 4, 5, 6));
	std::printf("addValues after concepts: %d \n", addAllValues(1, 2, 3, 4, 5, 6));
	std::printf("sum<unsigned i>(): %d \n", sum<5>(10));
}

struct Test 
{ 
	friend constexpr std::strong_ordering operator<=>(const Test& rhs, const Test& lhs) = default;  
};

struct Test1 { };

inline void compileTimePredicate_Concepts()
{
	std::printf("\n---compileTimePredicate with Concepts---\n");

	/* Use case of concepts in conditional checks!*/

	fmt::print("std::three_way_comparable<Test>: {}\n", std::three_way_comparable<Test>);
	fmt::print("std::three_way_comparable<Test1>: {}\n", std::three_way_comparable<Test1>);
	
	fmt::print("std::three_way_comparable<int>: {}\n", std::three_way_comparable<int>);
	fmt::print("std::three_way_comparable<double>: {}\n", std::three_way_comparable<double>);

	static_assert(std::three_way_comparable<std::string>);

	if constexpr (std::three_way_comparable<Test1>)
	{
		fmt::print("std::three_way_comparable<Test1>: True!\n");
	}
	else
	{
		fmt::print("std::three_way_comparable<Test1>: False!\n");
	}

	if constexpr (std::three_way_comparable<std::vector<int>>)
	{
		fmt::print("std::three_way_comparable<std::vector<int>>: True!\n");
	}
	else
	{
		fmt::print("std::three_way_comparable<std::vector<int>>: False!\n");
	}

}

