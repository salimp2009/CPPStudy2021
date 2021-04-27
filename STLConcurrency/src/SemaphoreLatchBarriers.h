#pragma once

#include "ConcurrencyUtility.hpp"

#if _HAS_CXX20

inline void Semaphore_Example()
{
	std::printf("\n--------------- Semaphore C++20----------------------\n");

	/* this example for one time notification; the template parameter sets the max thread count
		the initialization value sets the current count value; they can be different!!!
	*/

	std::vector<int> myVec{};
	/*in the e.g. below;  the count value can change between 0 and 1;
		release sets the value to 1 and unblocks the waiting thread and acquire decreases 
		the counter back zero 
	*/
	std::counting_semaphore<1> prepareSignal{ 0 };

	auto prepareWork = [&]() noexcept
	{
		myVec = { 1,0,3 };
		std::printf("Sender: data ready!\n");
		/* current MSVC implementation seq order but there is a note as it should memory order release*/
		/* release increase the value of counter*/
		prepareSignal.release();
	};

	auto completeWork = [&]() noexcept
	{
		std::printf("Consumer: Waiting for data!\n");
		/* acquire decrease the value of the counter*/
		prepareSignal.acquire();
		myVec[2] = 255;
		std::printf("Consumer: Completed Work!\n");
		printCont(myVec);
		std::printf("\n");		
	};

	std::thread th1{ prepareWork };
	std::thread th2{ completeWork };

	th1.join();
	th2.join();

}



#endif