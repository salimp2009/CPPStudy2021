#include "ConcurrencyPCH.h"
#include "FuturesBasics.h"
#include "MemoryOrderBasics.h"



int main()
{
	//FutureBasics_Test();
	//Futures_WaitingTwoTasks();
	//SharedFutures_Example();
	//ThreadPromises_Example();
	//MutexLock_Basics();
	//ConditionVariable_Basics();
	//Atomics_Basics();
	//AtomicFlag_Basics();
	//SpinLock_Example();
	//AtomicFlag_ThreadSync();
	//AtomicTypes_Operations();
	//SharedPtr_AtomicOps();
	//AtomicRef_Example();
	//AcquireRelease_Example();
	//ReleaseSemantics_Example();
	AcquireConsumeRelease_Example();

	/* C++17 add to optimize the cached either for one thread sees one cache or multiple threads see the see same cache */
	
	/* "If you want to access two different (atomic) objects with the same thread use alignas with the size of constructive
		or smaller"
	*/
	/* "hardware_constructive_interference_size is the recommended maximum size of contiguous
		memory within which two objects are placed in the same L1 cache line"
	*/
	//std::cout <<"hardware_constructive_interference_size: " <<std::hardware_constructive_interference_size << '\n';

	/* "If you want to access two different (atomic) objects with different threads: 
		use alignas at least with the size of destructor or smaller ; sharing same cache is thread safe but expensive !!!"
	*/
	//std::cout <<"hardware_destructive_interference_size: " <<std::hardware_destructive_interference_size << '\n';

}