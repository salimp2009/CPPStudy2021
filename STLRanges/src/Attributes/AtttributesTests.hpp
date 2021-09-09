#pragma once
#include "RangesPCH.hpp"
#include "AttributesCpp20.hpp"

inline void AttributesTest1()
{
	std::printf("\n-AttributesTest1-\n");

	int* val = create<int>(5);
	delete val;

	// memory leak
	create<int>(5);

	errorProneFunction();

	Mytype(5, true);

	std::printf("\n-AttributesTest2-\n");
	std::printf("\n-AttributesTest3-\n");

	

}
