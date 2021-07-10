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

	auto timezoneHere = std::chrono::current_zone();
	auto timezoneUTC = std::chrono::locate_zone("Europe/Istanbul");

	fmt::print("timezoneHere (current_zone): {0} \nUTC; locate_zone: {1}\n", timezoneHere->name(), timezoneUTC->name());
}

template<typename ZonedTime>
auto getMinutes(const ZonedTime& zonedTime)
{
	return std::chrono::floor<std::chrono::minutes>(zonedTime.get_local_time());
}

void printStartEndTimes(const std::chrono::local_days& localDay)
{

}

inline void variousTimeZones()
{
	std::printf("\n--variousTimeZones--\n");

}

