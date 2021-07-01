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
	//works for STL containers and all STL like container types(not checked!)
	std::vector<int> vec1{ 1,2,3,4,5,6,7,8,9,10 };
	auto noOfDeletedElems = std::erase_if(vec1, [](auto&& elem) { return elem % 2 == 0; });
	fmt::print("revised vec1: {}, number of deleted elems: {}\n", vec1, noOfDeletedElems);

	std::string testStrng = "this has a big E";
	noOfDeletedElems = std::erase(testStrng, 'E');
	fmt::print("revised string: {}, number of deleted elems: {}\n", testStrng, noOfDeletedElems);

	std::deque deq{ 1,2,3,4,5,6,7,8,9 };
	noOfDeletedElems = std::erase_if(deq, [](auto elem) {return elem % 2 == 1; });
	fmt::print("revised deque: {}, number of deleted elems: {}\n", deq, noOfDeletedElems);

	std::list lst1{ 11,22,33,44,55,77,65 };
	noOfDeletedElems = std::erase(lst1, 22);
	fmt::print("revised list: {}, number of deleted elems: {}\n", lst1, noOfDeletedElems);

}

inline void checkwithContains()
{
	std::printf("\n--- checkwithContains---\n");

	auto checkElements = []<class Container, typename... T>(const Container& container, T&&... values)
	{
		return (container.contains(values) && ...);
	};

	std::set<int> mySet{ 1,2,3,4,5,6,7,8,9,10 };

	auto result = checkElements(mySet, 1);
	fmt::print("contains result: {}\n", result);
	
	// contains check if the key exits ; does not look for the value for the unordered / ordered maps, sets...
	std::unordered_map<int, std::string> myMap = { {49, "Salim"}, {48, "Didem"}, {16, "Demir"} };
	result = checkElements(myMap, 49);
	fmt::print("contains result: {}\n", result);

	result = checkElements(myMap, 57);
	fmt::print("contains result: {}\n", result);

	result = checkElements(myMap, 49, 48);
	fmt::print("contains result: {}\n", result);
}

inline void stringPrefixSuffixCheck()
{
	std::printf("\n--stringPrefixSuffixCheck--\n");

	auto startsWith = [](std::string_view str, auto prefix)
	{
		fmt::print("{} starts_with [{}]: {}\n",str, prefix, str.starts_with(prefix));
	};

	auto endsWith = [](std::string_view str, auto prefix)
	{
		fmt::print("{} ends_with [{}]: {}\n", str, prefix, str.ends_with(prefix));
	};

	std::string str1 = "HelloWorld";
	startsWith(str1, std::basic_string_view("Hello"));
	startsWith(str1, std::basic_string_view("World"));
	startsWith(str1, 'H');
	
	endsWith(str1, std::basic_string_view("Hello"));
	endsWith(str1, std::basic_string_view("World"));
	endsWith(str1, 'H');
	endsWith(str1, 'd');
}

inline void safeIntegerComparision()
{
	std::printf("\n--stringPrefixSuffixCheck--\n");

	int x = -3;
	unsigned int y = 7;

	// give result as false since x is converted unsigned int and it is way bigger than 7 
	// since there is 1 at the left most of the binary to express negative number when converted to unsigned the number becomes 2^32
	//fmt::print("-3<7: {} ", x,y);  
	fmt::print("-3<7: {}\n", std::cmp_less(x,y));
	fmt::print("-3<=7: {}\n", std::cmp_less_equal(x,y));
	fmt::print("-3!=7: {}\n", std::cmp_not_equal(x,y));
	fmt::print("-3==7: {}\n", std::cmp_equal(x,y));
	fmt::print("-3>7: {}\n", std::cmp_greater(x,y));
	fmt::print("-3>=7: {}\n", std::cmp_greater_equal(x,y));
	
}


