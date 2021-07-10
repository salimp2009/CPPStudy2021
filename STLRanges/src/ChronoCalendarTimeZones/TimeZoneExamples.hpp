#pragma once
#include "RangesPCH.hpp"

inline void localTimeTest1()
{
	std::printf("\n--- localTime---\n");

	using namespace std::chrono_literals;
	using namespace std::chrono;

	fmt::print("ISA TimeZone tzdb version: {}\n", std::chrono::get_tzdb().version);

	auto utcTime = std::chrono::system_clock::now();
	fmt::print("UTC Time : {}\n", utcTime);

	auto localTime = std::chrono::zoned_time(std::chrono::current_zone(), utcTime);
	fmt::print("localTime: {0}\n", localTime);
	fmt::print("localTime(truncated to secs): {}\n", std::chrono::floor<std::chrono::seconds>(localTime.get_local_time()));

	auto offset = localTime.get_info().offset;
	fmt::print("UTC offset : {}\n", std::chrono::duration_cast<hours>(offset));

}
