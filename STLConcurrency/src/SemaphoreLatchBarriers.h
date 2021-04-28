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
		myVec = { 1, 0, 3 };
		
		/* current MSVC implementation seq order but there is a note as it should memory order release*/
		/* release increase the value of counter*/
		std::printf("Sender: data ready!\n");
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

	std::thread th2{ completeWork };
	std::thread th1{ prepareWork };
	std::thread th1a{ prepareWork };
	
	th2.join();
	th1.join();
	th1a.join();
	
}

inline void Latch_Example()
{
	std::printf("\n--------------- Latch C++20----------------------\n");
	/*"- Latches and barriers are coordination types that enable some threads to block until a counter
		becomes zero.
	   - You can use a std::latch only once, but you can use a std::barrier more than once.
	   - A std::latch is useful for managing one task by multiple threads. A std::barrier helps managing repeated
		tasks by multiple threads."
	  */
	std::latch workDone(6);
	
	/* ALTERNATIVE USING A BOSS to send all workers home*/
	//std::latch goHome(1);

	/* this is used only not to cause interleaving output; alternative might be c++20 new aysnch stream*/
	std::mutex coutMutex; 


	auto synchronizedOut = [&](std::string_view sv)
	{
		std::lock_guard<std::mutex> lockedOut{ coutMutex };
		fmt::print("{}\n", sv);
	};

	auto Worker = [&](std::string name)
	{
		/* notify when the work is done!!!*/
		synchronizedOut(name + "; " + "Work Done!");
		
		/* arrive_wait is combination of countdown and wait() until it reaches zero; NO Boss Scenario*/
		workDone.arrive_and_wait(); 

		/* USED with BOSS sending scenarioswait before go Home !!!*/
		//workDone.count_down();
		//goHome.wait();
		synchronizedOut(name + " Goodbye");

	};

	std::thread th1(Worker, "  Herb");
	std::thread th2(Worker, "    Scott");
	std::thread th3(Worker, "     Salim");
	std::thread th4(Worker, "      Bjarne");
	std::thread th5(Worker, "		Andrei");
	std::thread th6(Worker, "		 David");

	/* Commented out version is used with a BOSS scenario*/
	/* the main(boss thread waits until all workers done*/
	//workDone.wait();

	/* once all work done decrease the other latch with has initiliazed with 1 to 
		all workers are waiting on the latch goHome until it becomes zero!!!
	*/
	//goHome.count_down();

	//std::printf("GO HOME GUYS!!!\n");

	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();

}

inline void Barrier_Example()
{
	std::printf("\n--------------- Barrier C++20----------------------\n");

	/*Two difference between latches and barriers; Barriers can be used more than once and 
	  can be reset to different number threads for the next iteration;
	*/
	/* you can pass in a nothrow completion function for the barrier when the counter reaches zero it runs that function
		e.g: below there is a lambda function and it is invoked when counter reaches zero; not per each thread
	*/
	std::barrier workDone(6, []() noexcept
		{
			static auto completeMessage = "All Work Done!";
			fmt::print("{}!\n", completeMessage);
		}
	);
	
	/* USED in prev version of the example but kept it in case*/
	//std::mutex coutMutex;

	auto synchronizedOut = [/*&*/](std::string_view sv)
	{
		/* a lock is not need according to the example as each thread get its own copy of lambda*/
		//std::lock_guard<std::mutex> lockedOut{ coutMutex };
		fmt::print("{}\n", sv);
	};


	auto FullTimeWorker = [&](std::string name)
	{
		synchronizedOut(name + "; " + "Morning Work Done!");
		/* arrive_wait is combination of countdown and wait() until it reaches zero; */
		workDone.arrive_and_wait();
		synchronizedOut(name + "; " + "Afternoon Work Done!");
		/* reuse the barrier to so the work comes and wait untill all work is done !*/
		workDone.arrive_and_wait();
		synchronizedOut(name + "; " + "Goodbye Going Home!");

	};


	auto PartTimeWorker = [&](std::string name)
	{
		synchronizedOut(name + "; " + "Morning Work Done!");
		/* arrive_drop is combination of countdown and wait() and also deduct from number of thread to be used for the next iteration
		   until it reaches zero; 
		*/
		workDone.arrive_and_drop();
	};


	std::thread th1(FullTimeWorker, "  Herb");
	std::thread th2(FullTimeWorker, "    Scott");
	std::thread th3(PartTimeWorker, "     Salim");
	std::thread th4(FullTimeWorker, "      Bjarne");
	std::thread th5(PartTimeWorker, "		Andrei");
	std::thread th6(PartTimeWorker, "		 David");

	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
}


#endif