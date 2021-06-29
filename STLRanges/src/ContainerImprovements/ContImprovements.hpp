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

inline void makeShared()
{
	std::printf("\n---makeShared---\n");

	// before c++20 ; this would be ; std::shared_ptr<double[]> dblPtr(new double[1024])
	// std::make_shared do not allow custom deleters and 
	// if the user defined class uses class specific ::new overload then make_shared does not use it; prefer the old way in that case
	// make_shared will prevent leaks in case there is an exepception thrown while it is not fully constructed
	std::shared_ptr<double[]> dblPtr = std::make_shared<double[]>(1024);
	std::shared_ptr<double[]> dblPtr2 = std::make_shared<double[]>(100, 20.0); // 100 elements with value zero

	fmt::print("dblPtr[0]: {}\n", dblPtr[0]);
	fmt::print("dblPtr2[0]: {}\n", dblPtr2[0]);

}

inline void eraseif()
{
	std::printf("\n--- eraseif---\n");
	//works for STL containers and all container types
	std::vector<int> vec1{ 1,2,3,4,5,6,7,8,9,10 };
	auto noOfDeletedElems = std::erase_if(vec1, [](auto&& elem) { return elem % 2 == 0; });
	fmt::print("revised vec1: {}, number of deleted elems: {}\n", vec1, noOfDeletedElems);

	std::string testStrng = "this has a big E";
	noOfDeletedElems = std::erase(testStrng, 'E');
	fmt::print("revised string: {}, number of deleted elems: {}\n", testStrng, noOfDeletedElems);

	
}
