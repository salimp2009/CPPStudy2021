#pragma once
#include "ConcurrencyPCH.h"

#include "AtomicCpp20.hpp"

inline void AtomicRef()
{
	std::printf("\n-- AtomicRef--\n");

	ExpensiveToCopy2 expCopy{};

	count(expCopy);

	fmt::print("counter: {} \n", expCopy.counter);

	Counters count{ 4,5 };

	std::atomic_ref<Counters> atmCounters{ count };

	fmt::print("Before value change: atmCounters.a: {}, b: {} \n", atmCounters.load().a, atmCounters.load().b);

	count.a = 6;
	count.b = 7;

	fmt::print("After value change: atmCounters.a: {}, b: {} \n", atmCounters.load().a, atmCounters.load().b);

	fmt::print("Counters is_lock_free(): {}", atmCounters.is_lock_free());

}