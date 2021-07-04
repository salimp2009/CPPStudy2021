#pragma once
#include "RangesPCH.hpp"

inline void timeofDay()
{
	std::printf("\n--- timeofDay---\n");

	using namespace std::chrono_literals;

	// below construct gives a total duration which is the time from midnight; e.g: 10h will 10::00 am in the morning
	auto timeofDay = std::chrono::hh_mm_ss(10.5h + 98min + 2020s+ 0.5s);

	fmt::print("timeofDay: {}\n", timeofDay);
	fmt::print("timeofDay.hours(): {}\n", timeofDay.hours());
	fmt::print("timeofDay.minutes(): {}\n", timeofDay.minutes());
	fmt::print("timeofDay.seconds(): {}\n", timeofDay.seconds());
	fmt::print("timeofDay.subseconds(): {}\n", timeofDay.subseconds());
	fmt::print("timeofDay.to_duration(): {}\n", timeofDay.to_duration());

	fmt::print("std::chrono::hh_mm_ss(45700.5s) {}\n", std::chrono::hh_mm_ss(45700.5s));

}

