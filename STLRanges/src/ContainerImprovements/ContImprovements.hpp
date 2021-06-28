#pragma once
#include "RangesPCH.hpp"

constexpr int maxElements()
{
	std::vector myVec = { 7,5,3,4 };
	std::sort(myVec.begin(), myVec.end());
	return myVec.back();
}


inline void ConstExpr_Vector()
{
	std::printf("\n---constexpr_vector---\n");

	// intellisense error but it works ; checked in compilerexplorer; note does not work in GCC 11.1 and Clang 12
	constexpr int value = maxElements();
	std::printf("%d", value);
}


inline void makeArray()
{
	std::printf("\n---makeArray---\n");

	// creates const char* array[]; each element of the array is a c-string
	auto arr1 = std::to_array({ "testing an array" });
	fmt::print("c-string: {}, element count: {}\n", arr1, arr1.size());

	// creates a char array[] a c-string; each character is a seperate element of the array!
	auto arr2 = std::to_array("testing an array");
	fmt::print("char array: {}, element count: {} \n", arr2, arr2.size());



}
