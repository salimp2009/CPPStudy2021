#pragma once

#include "TupplePairUtilities.hpp"
#include "Allocators/tracknew.hpp"
//#include "AllocationMetrics.h"



inline void PmrMemoryResource_Basics()
{
	fmt::print("\n---------Pmr Memory Resource w/ Standart Alloc---------\n");

    //TrackNew::reset();
   // AllocationMetrics::reset();
   // AllocationMetrics::printAllocMetrics();
    std::vector<std::string> vecStrng;
    for (auto i = 0; i < 1000; ++i)
    {
       vecStrng.emplace_back("just a non-SSO string");
       
    }
    //AllocationMetrics::printAllocMetrics();
    //TrackNew::status();
   // std::cout << allocCount <<", size: "<<allocSize<<'\n';
  
}

inline void PmrMonotonicBuffer_Basics()
{
    fmt::print("\n---------------StackAllocator_MemoryPool-------------------------\n");
      
    static std::array<std::byte, 256> buffer;

    std::cout << &*(buffer.data()) << '\n';

    for (int num : {1000, 2000, 500, 2000, 3000, 50000, 1000})
    {
        std::printf("--check with %d elements\n", num);
        TrackNew::reset();
        // AllocationMetrics::reset();

        std::pmr::monotonic_buffer_resource pool{ buffer.data(), buffer.size() };
        std::pmr::vector<std::pmr::string> coll{ &pool };
        for (auto i = 0; i < num; ++i)
        {
            coll.emplace_back("just a noo00000000000ooooon-SSO string");

        } 
        // AllocationMetrics::printAllocMetrics();
        TrackNew::status();

        }
}

inline void PmrSynchronizedPool_Reason()
{
    fmt::print("\n---------------Example to Show SynchronizedPool_Reason-------------------------\n");
    /* Example shows the address of each item in map can  be spread out in the memory
        which is in-efficient and also cause memory fragmentation that is why using a memory source that is allocated
        will make sure the items are stored contigously ; see next pmr::asynch example for that
    */
    std::map<long, std::string>coll1;

    for (int i = 0; i < 10; ++i)
    {
        std::string s{ "Customer: " + std::to_string(i) };
        coll1.emplace(i, s);
    }

    for (const auto& elem: coll1)
    {
        static long long lastVal = 0;
        long long val = reinterpret_cast<long long>(&elem);
        fmt::print("diff: {}\n", (lastVal - val));
        lastVal = val;
    }
}


inline void PmrSynchronizedPool_Basics()
{
    fmt::print("\n--------------PmrSynchronizedPool_Basics-------------------\n");
    
    /*if not specified this will use a default memory resource and synchronize_pool is thread safe!*/
    std::pmr::synchronized_pool_resource pool;
    std::pmr::map<long, std::pmr::string>coll2{ &pool };

    for (int i = 0; i < 10; ++i)
    {
        std::string s{ "Customer: " + std::to_string(i) };
        coll2.emplace(i, s);
    }

    for (const auto& elem : coll2)
    {
        static long long lastVal = 0;
        long long val = reinterpret_cast<long long>(&elem);
        fmt::print("diff: {}\n", (lastVal - val));
        lastVal = val;
    }
}

inline void PmrMonotonicBuff_SynchPool()
{
    fmt::print("\n------Using Pmr MonotonicBuff andSynchPool---------\n");
    TrackNew::reset();

    /*allocated chunk of memory and start with 10k and no deallocation*/
    std::pmr::monotonic_buffer_resource keepAllocatedPool{ 10000 };
    /* synch pool will use first allocated at  monotonic buffer until it is full
       if needed synch will ask more and monotonic_buffer will allocate more
    */
    std::pmr::synchronized_pool_resource pool{ &keepAllocatedPool };

    for (int j = 0; j < 100; ++j)
    {
       std::pmr::vector<std::pmr::string> coll3{ &pool };
       for (int i = 0; i < 100; ++i)
       {
           coll3.emplace_back("just a non-SSO string");
       }

      
    }        // deallocations from pmr::Vector are given back to back to pool but not deallocated
    TrackNew::status();
    // the main buffer has not deallocated anythng since it still exists;
} // now the lifetime ends and the buffer deallocated all the memory







