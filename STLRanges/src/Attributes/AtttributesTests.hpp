#pragma once
#include "RangesPCH.hpp"
#include "AttributesCpp20.hpp"

inline void AttributesTest1()
{
	std::printf("\n-AttributesTest1-\n");

	// this should create a Warning since it has been changed in C++20 ; added [[nodiscard]] attribute so it does not become a blocking function
	std::future<int> f1 = std::async(std::launch::async, []() { return 8; });

	int* val = create<int>(5);
	delete val;

	//auto futval = f1.get();

	// memory leak
	create<int>(5);

	errorProneFunction();

	Mytype(5, true);
//
}

inline void NoUniqueAddressTest()
{
	std::printf("\n-NoUniqueAddress-\n");

	fmt::print("size of empty: {}\n", sizeof(Empty));
	fmt::print("size of int: {}\n", sizeof(int));

	fmt::print("size of NoUniqueAddress=sizeof(int): {}\n", sizeof(NoUniqueAddress));
	fmt::print("size of UniqueAddress=sizeof(int): {}\n", sizeof(UniqueAddress));



}
