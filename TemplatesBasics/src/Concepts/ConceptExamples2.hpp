#pragma once
#include "Templpch.h"

#include "ConceptsDispatch.hpp"

inline void conceptBasedDispatch()
{
	std::printf("\n---conceptBasedDispatch---\n");

	std::array<char, 16> ackData;
	std::array<char, 100> payLoadData;

	Send(ackData);
	Send(payLoadData);
}


std::integral auto getIntegral(int val)
{
	return val;
}
inline void placeHolders_Concepts()
{
	std::printf("\n---place Holders Concepts--\n");

	std::vector vec1 = { 1,2,3,4,5 };
	for (const std::integral auto& elem : vec1)
	{
		fmt::print("{} ", elem);
	}
	std::printf("\n");

	std::integral auto b = true;
	fmt::print("b: {}\n", b);

	auto integ1 = getIntegral(10);
	fmt::print("integ1: {}\n", integ1);

}