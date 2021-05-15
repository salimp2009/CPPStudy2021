#pragma once

#include "STLpch.h"

std::optional<int> asInt(const std::string& s)
{
	std::optional<int>ret;
	try
	{
		ret= std::stoi(s);
	}
	catch (...)
	{	
	}
	return ret;
}

inline void Optional_Basics()
{
	std::printf("\n-------------Optional_Basics C++17-------------\n");
	for (auto s : { "42", "077", "hello", "0x33" })
	{
		auto opt=asInt(s);
		//if (opt.has_value()) 
		//	std::cout << *opt << '\n';
		//else
		//	std::cout <<"cannot convert!!" << '\n';

		/* value_or() allocates memory therefore prefer the ALTERNATIVE below!*/
		//std::cout << "s: " << opt.value_or(0);

		// ALTERNATIVE to value or does not allocate memory
		fmt::print("optinional value: {}\n", (opt ? *opt : 0));
	}
	
}


inline void Variant_Basics()
{
	std::printf("\n-------------Variant_Basics C++17-------------\n");

	std::variant<int, std::string> var1{ "hi" };

	fmt::print("index of var1: {}\n", var1.index());
	
	fmt::print("value of var1: {}\n", std::get<1>(var1));

	std::variant<std::monostate, int, int, std::string> var2; 
	fmt::print("index of var2: {}\n", var2.index());

	std::variant<std::complex<double>> var3{ std::in_place_index<0>, 12.2, 2.25 };
	fmt::print("value of var1: {}\n", std::get<0>(var3));

	

}
