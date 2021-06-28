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
	auto arr1a = std::to_array("testing an array");
	fmt::print("char array: {}, element count: {} \n\n", arr1a, arr1a.size());

	auto arr2 = std::array{ 1, 2, 3, 4, 5 };
	fmt::print("array: {}, element count: {}\n", arr2, arr2.size());
	
	auto arr2a = std::to_array({ 1,2,3,4,5 });
	fmt::print("to_array: {}, element count: {}\n\n", arr2a, arr2a.size());
	
	auto arr3 = std::to_array<double>({ 0,1,3 });
	fmt::print("to_array<double>: {}, typeid: {}, size: {}\n\n", arr3, typeid(arr3[0]).name(), arr3.size());

	auto arr4 = std::to_array<std::pair<int, double>>({ { 3,4.0 }, {5,6.2}, { 25,10.25 } });
	
	fmt::print("to_array<pair>: {}, typeid: {}, size: {}\n\n", arr4, typeid(arr4[0]).name(), arr4.size());


}
