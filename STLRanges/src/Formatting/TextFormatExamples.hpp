#pragma once
#include "RangesPCH.hpp"
//#include "Formatting/CustomFormatter.hpp"
#include "Formatting/StockIndex.hpp"


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

inline void FormatwithLocales()
{
	std::printf("\n--FormatwithLocale--\n");
	using namespace std::string_literals;
	using namespace std::string_view_literals;


	// }} is an escape sequence; only } is printed
	fmt::print("{}", std::format("Having the  }} in a {}.\n", "string"));

	double pi = 3.14;
	int i = 1'024;

	auto us = "en_US.UTF-8"s;
	//de: is the language; German, en for English
	//_area = DE or US is the area
	//.code = is the code defines character encoding UTF-8 is Universal Character Set and Unicode standards; used on the internet as well
	// @modifier = is the modifier ; optional ; is allowed on some platforms to specify additional modifications, such as @euro for
	// using the euro symbol or @phone for sorting according to the telephone directory ;e.g.; de_DE.UTF-8@euro
	// language[_area[.code]][@modifier]
	auto locDE = std::locale("de_DE.UTF-8");
	auto locUS = std::locale(us);

	fmt::print("double format with locales:\n");
	fmt::print("{}", std::format(locDE, "\t\t in DE: {:L}\n", pi));
	fmt::print("{}", std::format(locUS, "\t\t in US: {:L}\n", pi));
	
	fmt::print("int-seperator format with locales:\n");
	fmt::print("{}", std::format(locDE, "\t\t in DE: {:L}\n", i));
	fmt::print("{}", std::format(locUS, "\t\t in US: {:L}\n", i));

}

inline void FormatFillAlign()
{
	std::printf("\n--FormatFillAlign--\n");

	int num = 2021;

	fmt::print("{}\n", std::format("{:6}", num));
	fmt::print("{}\n", std::format("{:6}", 'x'));
	fmt::print("{}\n", std::format("{:*<6}", 'x'));
	fmt::print("{}\n", std::format("{:*>6}", 'x'));
	fmt::print("{}\n", std::format("{:*^6}", 'x'));
	fmt::print("{}\n", std::format("{:6d}",num));
	
	// converts 'x' into numeric via ASCI Code; 'x'=120
	fmt::print("{}\n", std::format("{:6d}",'x'));  
	fmt::print("{}\n", std::format("{:6}", true));
}

inline void FormatSign()
{
	std::printf("\n--FormatSign--\n");

	fmt::print("{}\n", std::format("{0:}, {0:+}, {0:-}, {0: }", 0));
	fmt::print("{}\n", std::format("{0:}, {0:+}, {0:-}, {0: }", -0));
	fmt::print("{}\n", std::format("{0:}, {0:+}, {0:-}, {0: }", 1));
	fmt::print("{}\n", std::format("{0:}, {0:+}, {0:-}, {0: }", -1));
	
}

inline void CustomFormat_V1()
{
	std::printf("\n--CustomFormat_V1--\n");

	for (const auto& index : GetIndices())
	{
		//fmt::print("{}", std::format("{}\n", index));

		//std::cout << std::format("{}\n", index);
		std::cout << index.name() << " " << index.points() << "  "
			<< index.pointsDiff() << "  " << index.pointsPercent()
			<< '%' << '\n';
	}

	//for (const auto& index : GetIndices()) {
	//	std::cout << std::format("{}\n", index);
	//}

}







