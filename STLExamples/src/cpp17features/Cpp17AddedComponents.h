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
		std::cout << (opt ? *opt : 0) << '\n';
	}
	

}
