#pragma once

#include "ConcurrencyUtility.hpp"

/* movedf into global space on using in examples; othwerwise Dont Do this!!*/
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


inline void FutureBasics_Test()
{
	std::printf("\n---------------Future Basics-------------------------\n");

	auto func1 = []()->int { return doSomethng('.'); };
	auto func2 = []()->int { return doSomethng('+'); };
	
	/* start early call late pattern*/
	/* for lazy evaluation use;  std::async(std::launch::deferred, func1); will not be called until called by get() */
	std::future<int>result1 = std::async(std::launch::async, func1);
	
	fmt::print("starting func1 in the backgrnd and func2 in foregrnd!!!\n");

	int result2 = func2();
	auto result = result1.get() + result2;

	fmt::print("\nresult of func1 and func2 {}\n", result);

}


void Futures_WaitingTwoTasks()
{
	std::printf("\n---------------Future Waiting Two Tasks-------------------------\n");

	std::printf("starting two function async !!!\n");
	auto func1 = []()->int { return doSomethng('.'); };
	auto func2 = []()->int { return doSomethng('+'); };

	auto fut1 = std::async(func1);
	/*this might be deferred depending on threads available*/
	auto fut2 = std::async(func2);

	if (fut1.wait_for(std::chrono::seconds(0)) != std::future_status::deferred ||
		fut2.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)
	{
		
		// poll until at least one of the loops finished !!!
		while (fut1.wait_for(std::chrono::seconds(0)) != std::future_status::ready &&
			fut2.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
		{
			// let other threads do work (note this context switch and expensive)
			std::this_thread::yield();
		}
	}

	std::cout.put('\n').flush();

	try {
		fut1.get();
		fut2.get();
	}
	catch (const std::exception& e)
	{
		std::cerr << "\nEXCEPTION: " << e.what() << '\n';
	}

	std::printf("\nWaiting Two Tasks Example Done!\n");

}