#pragma once
#include "RangesPCH.hpp"


inline void oldwayFormatting()
{
	std::printf("\n--oldwayFormatting--\n");

	std::tuple values = { "Salim", 20123.13f, 2345.55, 1455.67f };

	fmt::print("{}\n", values);
	//old style formatting -8s; indicates a left aligned with a width of 8; 
	// %% is to print a percentage second one is to make sure it is not a format sign
	// printf is thread safe atomic and it prints all arguments at once as variadic therfore no interleavinf btween threads
	// but it is not type safe; not checks for types; 
	std::printf("%-8s, %8.2lf, %6.2lf, %4.2lf%%\n", std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values));

	fmt::print("{}", std::format("{:8}, {:>8.2f}, {:6.2f} {:.2f}% \n", 
							std::get<0>(values), std::get<1>(values), std::get<2>(values), std::get<3>(values)));

	std::string buffer;
	std::format_to(std::back_inserter(buffer), "Hello std::format {}", " c++20!");
	fmt::print("{}\n", buffer);
	buffer.clear();

	// format_to_n specifies the number of args , it does not take account if there is more args; e.g prints only Hello (5 chars)
	std::format_to_n(std::back_inserter(buffer), 5, "Hello std::format {}", " c++20!");
	fmt::print("{}\n", buffer);
}


