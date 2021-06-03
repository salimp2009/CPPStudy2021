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

}


