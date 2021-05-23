#pragma once
#include "STLpch.h"


template<class... Bases>
struct Overload : Bases...
{
	using Bases::operator()...;
};

/* this is not needed for C++20*/
template<class...T> 
Overload(T...)->Overload<T...>;

struct PrintVisitor
{
	void operator()(int i) { fmt::print("int: {}\n", i); }
	void operator()(float f) { fmt::print("float: {}\n", f); }
	void operator()(const std::string& s) { fmt::print("string: {}\n", s); }
};


inline void PrintVisitor_Variants()
{
	std::printf("\n---PrintVisitor_Variants---\n");
	std::variant<int, float, std::string> intFloatString;

	static_assert(std::variant_size_v<decltype(intFloatString)> == 3);

	std::visit(PrintVisitor{}, intFloatString);

	fmt::print("index = {}\n", intFloatString.index());
	
	intFloatString = 55.0f;
	fmt::print("index = {}\n", intFloatString.index());
	
	intFloatString = "Salim";
	fmt::print("index = {}\n", intFloatString.index());

	if (const auto intPtr = std::get_if<int>(&intFloatString))
	{
		fmt::print("intPtr: {0}", *intPtr);
	}
	else if (const auto floatPtr = std::get_if<float>(&intFloatString))
	{
		fmt::print("floatPtr: {0}", *floatPtr);
	}


	if (std::holds_alternative<int>(intFloatString))
	{
		fmt::print("the variant holds an int!\n");
	}
	else if (std::holds_alternative<float>(intFloatString))
	{
		fmt::print("the variant holds a float!\n");
	}
	else if (std::holds_alternative<std::string>(intFloatString))
	{
		fmt::print("the variant holds a string: {}!\n", std::get<std::string>(intFloatString));
	}
	 
	std::variant<std::vector<int>> vecInt{ std::in_place_index<0>, {1,2,3,4} };

	for (const auto& elem : *std::get_if<std::vector<int>>(&vecInt))
	{
		fmt::print("elem: {0} ", elem);
	}

	/* const char* is converted to bool in the below example!*/
	std::variant<std::string, int, bool> typeconversionVar = "Salim";
	fmt::print("\nindex of typeconversion var: {}\n", typeconversionVar.index());

	/*Ambigious variant; compiler cannot decide the type since it can be any of the given type below!!; GCC has a fix*/
	//std::variant<long, float, double> narrowingVar = 0;
}

inline void variantMultipleTest()
{
	struct mOpengl { };
	struct mDirectx { };
	struct mVulkan { };
	struct mMetal { };

	std::variant<mOpengl, mDirectx, mVulkan, mMetal> windowsRenderer{ mDirectx{} };
	std::variant<mOpengl, mDirectx, mVulkan, mMetal> linuxRenderer{ mVulkan{} };
	std::variant<mOpengl, mDirectx, mVulkan, mMetal> macOSRenderer{ mMetal{} };

	/* if you pass multiple variants then there have to be more overloads and it creates unneccessary code so prefer to use one*/
	std::visit(Overload{
		[](const mDirectx& dx) { std::cout<<"DirectX Renderer API !\n"; },
		[](const mMetal& met) {  std::cout << "Metal Renderer API !\n"; },
		[](const mOpengl& ogl) {  std::cout << "OpenGL Renderer API !\n"; },
		[](const mVulkan& vul) {  std::cout << "Vulkan Renderer API !\n"; },
		[](const auto& b) {std::cout << "invalid composition...\n"; },
		}, linuxRenderer);

}





