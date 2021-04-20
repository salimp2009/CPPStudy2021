#pragma once

#include "ConcurrencyUtility.hpp"


inline void FutureBasics_Test()
{
	std::printf("\n---------------Future Basics-------------------------\n");

	auto doSomethng = [](auto&& c)->int
	{
		std::mt19937 rnde(c);
		std::uniform_int_distribution<int> id(10, 100);

		for (int i{ 0 }; i < 10; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(id(rnde)));
			std::cout.put(c).flush();
		}

		return c;
	};

	auto func1 = [doSomethng]()->int { return doSomethng('.'); };
	auto func2 = [doSomethng]()->int { return doSomethng('+'); };
	
	/* start early call late pattern*/
	/* for lazy evaluation use;  std::async(std::launch::deferred, func1); will not be called until called by get() */
	std::future<int>result1 = std::async(std::launch::async, func1);
	
	fmt::print("starting func1 in the backgrnd and func2 in foregrnd!!!\n");

	int result2 = func2();
	auto result = result1.get() + result2;

	fmt::print("\nresult of func1 and func2 {}\n", result);

}
