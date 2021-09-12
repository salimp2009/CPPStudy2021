#pragma once
#include "RangesPCH.hpp"
#include "ImprovementsCPP20.hpp"

inline void RangeBasedForLoopInitialize()
{
	std::printf("\n- RangeBasedForLoopInitialize-\n");

	for (auto vec = std::vector{ 1,2,3,4,5 }; const auto & elem :vec)
	{
		std::printf("%d ", elem);
	}
	std::puts(" ");

	// classic way initializing the vector
	for (std::vector<int> vec2{ 1,2,3,4,5 }; const auto & elem :vec2)
	{
		std::printf("%d ", elem);
	}
	std::puts(" ");

	// initializer list example but initializer list can be written directly;  e.g for( auto elem : {1,2,3,4,5})
	for (auto InitList = { 100,200,300,400,500 }; auto elem:InitList)
	{
		std::printf("%d ", elem);
	}
	std::puts(" ");
	
}

inline void VirtualConstExprFunction()
{
	std::printf("\n-VirtualConstExprFunction-\n");

	constexpr X2 x2;
	constexpr X3 x3;
	constexpr auto val = x2.f();
	static_assert(x2.f() == 2);
	
	X1* xx1 = new X4;
	std::printf("x1: %d ", xx1->f());
	
}

