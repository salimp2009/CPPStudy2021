#pragma once

#include "TupplePairUtilities.hpp"
//#include "Allocators/tracknew.hpp"
#include "AllocationMetrics.h"



inline void PmrMemoryResource_Basics()
{
	fmt::print("\n---------Pmr Memory Resource w/ Standart Alloc---------\n");

    //TrackNew::reset();
    AllocationMetrics::reset();
    AllocationMetrics::printAllocMetrics();
    std::vector<std::string> vecStrng;
    for (auto i = 0; i < 1000; ++i)
    {
       vecStrng.emplace_back("just a non-SSO string");
       
    }
    AllocationMetrics::printAllocMetrics();
    //TrackNew::status();
   // std::cout << allocCount <<", size: "<<allocSize<<'\n';
  
}

inline void PmrMonotonicBuffer_Basics()
{
    fmt::print("\n---------------StackAllocator_MemoryPool-------------------------\n");

    //TrackNew::reset();
    AllocationMetrics::reset();
   
    std::array<std::byte, 200'000> buffer;

    std::pmr::monotonic_buffer_resource pool{ buffer.data(), buffer.size() };

    std::pmr::vector<std::string> coll{ &pool };

    for (auto i = 0; i < 1000; ++i)
    {
        coll.emplace_back("just a non-SSO string");

    }
    AllocationMetrics::printAllocMetrics();
    //TrackNew::status();
   // std::cout << allocCount <<", size: "<<allocSize<<'\n';

}



