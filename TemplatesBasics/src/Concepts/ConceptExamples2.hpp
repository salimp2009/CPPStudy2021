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