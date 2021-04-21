#pragma once

#include "ConcurrencyUtility.hpp"

#ifdef NDEBUG
	#define ASSERTM(exp, msg) assert ((void)0)
#else
	#define	ASSERTM(exp, msg) assert(((void)msg, exp))
#endif

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


inline void Futures_WaitingTwoTasks()
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

inline void SharedFutures_Example()
{
	std::printf("\n---------------Shared Futures-------------------------\n");

	auto getNumber = []()->int
	{
		std::printf("Enter a number: ");
		int num;
		std::cin >> num;
		ASSERTM(num, "no numbers read!!");
		return num;
	};

	auto doSomethn2 = [](char c, std::shared_future<int> f)
	{
		try
		{
			auto num = f.get();

			for (int i{0}; i<num; ++i)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				std::cout.put(c).flush();
			}

		}
		catch (const std::exception& e)
		{
			std::cerr << "Thread Exception!: " << e.what() << ", in thread id: " << std::this_thread::get_id() << '\n';
		}
	};

	/* read number into shared future async and use it doSomethn2 in multiple threads*/
	/* shared_futures are expensive; AVOID using them and dont use by cont& or & it may cause data races!!*/
	std::shared_future<int> f=std::async(getNumber);

	auto fut1 = std::async(std::launch::async, doSomethn2, '.', f);
	auto fut2 = std::async(std::launch::async, doSomethn2, '+', f);
	auto fut3 = std::async(std::launch::async, doSomethn2, '*', f);

	fut1.get(); fut2.get(); fut3.get();

	std::printf("\nShared Futures done!\n");


}

inline void ThreadPromises_Example()
{
	std::printf("\n---------------Threads with Promises-------------------------\n");


	auto doSomePromises = [](std::promise<std::string>& p)
	{
		try 
		{
			std::printf("enter a char ('x' for exception): ");
			char c = std::cin.get();
			if (c == 'x')
			{
				throw std::runtime_error(std::string("char ") + c + " read");
			}

			std::string s = std::string("char ") + c + " processed";
			/*store the result*/
			p.set_value(std::move(s));
		}
		catch (...)
		{
			/* store the exception if any occcurs*/
			p.set_exception(std::current_exception());
		}

	};


	try
	{
		/* the type of promise needs to match the result to get from the function
			in which the value is set with member function of std::promise via set_value()
		*/
		std::promise<std::string> p;

		/* promise can be passed by reference only since it will be modified*/
		std::thread t(doSomePromises, std::ref(p));

		/*ALTERNATIVE: std::future<std::string> futA(p.get_future());*/
		/* we need a future object to get the result from promise*/
		auto fut = p.get_future();

		t.join();

		fmt::print("Result from promise: {}", fut.get());

	}
	catch(const std::exception& e)
	{
		std::cerr << "EXCEPTION: "<<e.what()<<'\n';
	}
	catch (...)
	{
		std::cerr << "EXCEPTION ... " <<'\n';
	}

}