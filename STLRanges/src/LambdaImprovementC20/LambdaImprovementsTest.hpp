#pragma once
#include "RangesPCH.hpp"
#include "LambdaImprovements.hpp"


inline void LambdaCapturesInClass()
{
	std::printf("\n-LambdaCapturesInClass-\n");

	SomeClass somecls1;
	fmt::print("{}", somecls1.getTwiceValue());
}

