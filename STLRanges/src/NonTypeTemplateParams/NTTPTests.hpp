#pragma once
#include "RangesPCH.hpp"
#include "NonTypeTemplateParams.hpp"


inline void floatingPointNTTP()
{
	std::printf("\n-floatingPointNTTP-\n");

	// floating points are not equal 0.6-0.2 != 0.4 and uses different bit pattern when there is negative sign involved
	static_assert(! std::is_same_v<ADouble<+0.6 - 0.2>, ADouble<0.4>>);

	// +0.0 and -0.0 uses different bit pattern -1 is used to express negative sign at most left byte
	static_assert(!std::is_same_v<ADouble<+0.0>, ADouble<-0.0>>);

	// +0.0 == -0.0 is accepted equal in fp standarts
	static_assert(+0.0 == -0.0);

	// 0.1+0.1 == 0.2 and also uses same bit battern since no negative (but for number with more digits this might change due to machine Epsilon!!
	static_assert(std::is_same_v<ADouble<0.1 + 0.1>, ADouble<0.2>>);

	static_assert(+0.1+0.1 == 0.2);
}

inline void classTypeNTTP()
{
	std::printf("\n-classTypeNTTP-\n");

	fixed_string st1{ "hello classtype NTTP" };

	fmt::print("class literal fixed_string: {}\n", st1.data);

	printString<"hello fixed string">();

	FixedStringContainer<"hello fixedstring container">fstrCont{};
	fstrCont.print();
}

inline void FormatWithSpecifierCount()
{
	std::printf("\n-FormatWithSpecifierCount-\n");

	print(FormatString<"%s, %s\n">{}, "Hello", "FormatString");
	print("%s, %s\n"_fs, "Hello", "FormatString");

	// test to check match function woks as intended ; to be used in print function implementation
	static_assert(match<char*>('s'));
	static_assert(match<int>('d'));
	static_assert(match<double>('f'));
	fmt::print("match : {}", match<int>('d'));

	auto formt = "%s, %s\n"_fs;

	// compile error I needs to be expanded in paramater pack
	//IsMatching<char, decltype("Hello"), decltype("Mornig")>(formt.fmt.data);

	// Does not compile with MSVC ON VS Studio but compiles with MSVC, Clang12.01 and GCC11.01 no godbolt
	// 	https://godbolt.org/z/rrGsWW53r
	//print2("%s, %s\n"_fs, "Hello", "FormatString");
	

}



