#pragma once
#include "Concepts/ConceptsCustomDefined.hpp"

inline void SignedUnSignedIntegral_Func()
{
	std::printf("\n--- SignedUnSigned_Integral-\n");
	funct(-5);
	funct(5u);
	funct(5);
	funct(true);
	funct('c');

	static_assert(not (SignedIntegral<decltype(5.5)> || UnSignedIntegral<decltype(5.5)>));
	static_assert(ArithmeticType<decltype(5.5)>);
	static_assert(ArithmeticType<decltype(-5.5f)>);
	static_assert(ArithmeticType<bool>);
	static_assert(ArithmeticType<char>);

	std::printf("\n--- Equal Concept-\n");
	const std::unordered_set<int> set1{ 1,2,3,4,5 };
	const std::unordered_set<int> set2{ 5,2,1,4,3 };

	fmt::print("are equal sets: {}\n", areEqual(set1, set2));

}




