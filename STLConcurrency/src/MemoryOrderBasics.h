#pragma once

#include "ConcurrencyUtility.hpp"


inline void AtomicFlag_Basics()
{
	std::printf("\n---------------Atomic Flag------------------------\n");

	/* by default std::atomic_flag is guaranteed to be lock free ; 
	other alternative std::atomic are implementation defined
	*/
	/* the default constructor or below macro (needed in C++11) initializes to false !!!*/
	std::atomic_flag readyFlag= ATOMIC_FLAG_INIT; 

#if _HAS_CXX20
	std::cout<<readyFlag.test()<<'\n';
#endif


}

class spinlock
{
private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
	void lock() noexcept
	{
		/* spinlock should be used for very short time locking ; it wastes CPU cycles; prefer not to use it*/
		while (flag.test_and_set());
	}

	void unlock() noexcept
	{
		flag.clear();
	}

};


inline void SpinLock_Example()
{
	std::printf("\n---------------Spinlock Example-----------------------\n");

	spinlock spin;

	const auto workOnResource = [&spin](auto&& val) noexcept
	{
		spin.lock();
		fmt::print("working on resource : {}, by thread : {}\n", ++val, std::this_thread::get_id());
		spin.unlock();
	};

	int myval{ 20 };

	std::thread t1(workOnResource, std::ref(myval));
	std::thread t2(workOnResource, std::ref(myval));

	t1.join();
	t2.join();

}

#if _HAS_CXX20
	inline void AtomicFlag_ThreadSync()
	{
		std::printf("\n---------------Atomic Flag _ Thread Syncing Example-----------------------\n");

		std::vector<int> myVec;
		std::atomic_flag atomicFlag{};

		const auto prepareWork = [&myVec, &atomicFlag]() noexcept
		{
			myVec.insert(myVec.end(), { 0,1,0,3 });
			std::printf("sender: data is ready !\n");
			atomicFlag.test_and_set();
			/* C++20 addition*/
			atomicFlag.notify_one();
		};

		const auto completeWork = [&myVec, &atomicFlag]() noexcept
		{
			/* wait while it is false*/
			/* Notes from cppreference.com: "..more efficient than simple polling or pure spinlocks.
			   Due to the ABA problem, transient changes from old to another value and back to old might be missed, and not unblock."
			*/
			/* C++20 addition .wait() function*/
			atomicFlag.wait(false);
			myVec[2] = 2;
			//fmt::print("completed work: myvec : {}", fmt::join(myVec, ", "));
			std::printf("completed work!\n");
			for (auto elem : myVec)
			{
				std::printf("%i%s", elem, (elem != myVec.back() ? "," : "\n"));
			}
		};

		std::thread t1{ prepareWork };
		std::thread t2{ completeWork };

		t1.join();
		t2.join();
}

#endif

