#pragma once

#include "STLpch.h"
#include <any>

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
	fmt::print("value of var3: {}\n", std::get<0>(var3));

	std::variant<std::complex<double>> var4;
	var4.emplace<0>(12.2, 35.45);

	fmt::print("value of var4: {}\n", std::get<0>(var4));

	std::visit([](auto&& val) {fmt::print("val : {}\n", val); }, var1);
	var1 = 1;
	std::visit([](auto&& val) {fmt::print("revised val : {}\n", val); }, var1);
	var1 = 25;
	//std::visit([](auto&& val)
	//	{
	//		/* restores the default of the current alternative; e.g. it becomes empty string or empty int*/
	//		val = std::remove_reference_t<decltype(val)>{};
	//		fmt::print("revised val : {}\n", val);
	//	}, var1);

	//fmt::print("index of var1: {}\n", var1.index());

	auto doubleVal = [](auto& val)
	{
		/* since the val is a reference if we used std::is_same it will the address of the variable 
		   but if we check convertible than it compares the value
		*/
		if constexpr (std::is_convertible_v<decltype(val), std::string>)
		{
			val += val;
			fmt::print("val : {}\n", val);
		}
		else
		{
			val *= 2;
			fmt::print("val : {}\n", val);
		}
	};

	std::visit(doubleVal, var1);
}

inline void StdAny_Basics()
{
	std::printf("\n-------------std::any-------------\n");
	/* Avoid using std::any; bring extra memory allocations for a big type
	  and the size is quite big!!!!
	*/
	std::any aVal(12);
		
	if (aVal.has_value() && aVal.type()==typeid(int))
	{
		fmt::print("any val : {}\n", std::any_cast<int>(aVal));
	}
	
}

inline void StdByte_Basics()
{
	std::printf("\n-------------std::byte------------\n");

	/* Only binary operations allowed*/
	std::byte b1{0x3f};
	std::byte b2{ 0b1111'0000 };
	std::byte b3[4]{ b1, b2, std::byte{1} }; // Any array of std::byte , last value becomes zero since nothing is passed 

	std::cout <<"b1: "<<std::to_integer<int>(b1) << '\n';

	if (b1 == b3[0])
	{
		b1 <<= 1;
	}

	std::cout << "b1 revised: " << std::to_integer<int>(b1)<<'\n';
	std::cout << "sizeof b1: "<<sizeof b1 << '\n';

}


