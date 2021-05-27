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
