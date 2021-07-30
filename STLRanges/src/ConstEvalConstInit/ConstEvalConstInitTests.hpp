#pragma once
#include "RangesPCH.hpp"
#include "ConstEvalConsInit.hpp"

constexpr auto res1 = square(5);

// constinit does not imply constness
constinit auto res2 = square(5);

inline void constEvalSqr()
{
	std::printf("\n-constEvalSqr-\n");
	constexpr auto result = res1;
	
	// constinit has to be static or thread_storage 
	//constinit auto result2 = res2;
	static_assert(result == 5 * 5);

	const int a = 5;
	auto result3 = res2;
	fmt::print("square(a): {0}, square(5): {1}", square(a), square(5));
	static_assert(result == square(a));
	static_assert(result == square(5));

	constinit thread_local auto threadData = square(5);
	// does not Compile it ask for constness
	//static_assert(threadData == square(5));

	int result4 = square(5);
}