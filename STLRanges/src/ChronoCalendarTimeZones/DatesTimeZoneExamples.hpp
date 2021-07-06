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

	fmt::print("std::chrono::is_am(5h): {}\n", std::chrono::is_am(5h));
	fmt::print("std::chrono::is_pm(15h): {}\n", std::chrono::is_pm(15h));

	fmt::print("std::chrono::make12(5h): {}\n", std::chrono::make12(5h));
	fmt::print("std::chrono::make12(0h): {}\n", std::chrono::make12(0h));
	fmt::print("std::chrono::make24(5h, true): {}\n", std::chrono::make24(5h, true));
	fmt::print("std::chrono::make24(5h, true): {}, pm?: {}\n", std::chrono::make24(5h, true), std::chrono::is_pm(std::chrono::make24(5h, true)));
}

inline void calendarDates()
{
	std::printf("\n--- calendarDates---\n");
	using namespace std::chrono_literals;

	constexpr auto yearMonthDay = std::chrono::year_month_day(std::chrono::year{ 1920 }, std::chrono::month{ 12 }, std::chrono::day{ 15 });
	fmt::print("std::chrono::year_month_day(1920, 12, 15): {}\n", yearMonthDay);

	constexpr auto yearMonthDay2 = std::chrono::year_month_day(std::chrono::year{ 1920 }/std::chrono::month{ 12 }/std::chrono::day{ 15 });
	fmt::print("std::chrono::year_month_day(1920/12/15): {}\n", yearMonthDay2);

	constexpr auto yearMonthDay3 = std::chrono::year_month_day( 1920y/12/15);
	fmt::print("std::chrono::year_month_day(1920/12/15): {}\n", yearMonthDay3);

	constexpr auto yearMonthDay4 = std::chrono::year{1920} / 12 / 15;
	fmt::print("std::chrono::year(1920)/12/15: {}\n", yearMonthDay4);

	constexpr auto yearMonthDay5 = 1920y/12/15;
	fmt::print("1920y/12/15: {}\n", yearMonthDay5);

	constexpr auto yearMonthDay6 = 1920y / std::chrono::December / 15;
	fmt::print("1920y/December/15: {}\n", yearMonthDay6);

	constexpr auto yearMonthDayLast = std::chrono::year{ 2010 } / std::chrono::March / std::chrono::last;
	fmt::print("2010/March/LastDay: {}\n", yearMonthDayLast);

	auto yearMonthWeekday{ std::chrono::year{2021} / std::chrono::January / std::chrono::Wednesday[1]};
	fmt::print("2021/January/Wednesday[1]: {}\n", std::chrono::year_month_day(yearMonthWeekday));

	constexpr auto ym{ std::chrono::year(2021) / std::chrono::January };
	constexpr auto wdi{ std::chrono::Wednesday[1] };
	auto ymwdi{ ym / wdi };
	auto index = ymwdi.index() + 1;
	auto weekday = ymwdi.weekday() + std::chrono::days(1);
	ymwdi = { ymwdi.year() / ymwdi.month() /weekday[index] };
	fmt::print("2021/January/2ndThursday (14th): {}\n", std::chrono::year_month_day(ymwdi));

	constexpr auto yearMonthWeekdayLast = std::chrono::year(2010) / std::chrono::March / std::chrono::Monday[std::chrono::last];
	fmt::print("yearMonthWeekdayLast: {0}: {1}\n", yearMonthWeekdayLast, std::chrono::year_month_day(yearMonthDayLast));

	// better to use namespace std::chrono!!
	fmt::print("yearMonthWeekdayLast: {0}\n", std::chrono::year_month_weekday_last(2010y, std::chrono::month(std::chrono::March), std::chrono::weekday_last(std::chrono::Monday)));

}

inline void calendarDates2()
{
	std::printf("\n--- calendarDates2---\n");
	using namespace std::chrono_literals;

	constexpr auto day1 = std::chrono::day(19);	
	constexpr auto day2{ 12d };
	fmt::print("day1: {0}, day2: {1}\n", day1, day2);

	constexpr auto year1 = std::chrono::year{ 2021 };
	fmt::print("year1: {0}\n", year1);
	
	constexpr auto month1 = std::chrono::March;
	constexpr auto month2 = std::chrono::month{ 3 };
	fmt::print("month1: {0}; month2: {1}\n", month1, month2);

	constexpr auto weekday1 = std::chrono::weekday{ 2 };
	constexpr auto weekday2 = std::chrono::Tuesday;
	constexpr auto weekday_indexed3 = std::chrono::Tuesday[2];
	fmt::print("weekday1: {0}; weekday2: {1}, weekday-indexed3: {2}\n", weekday1, weekday2, weekday_indexed3);
	fmt::print("weekday_indexed3.weekday(): {0}, weekday_indexed3.index(): {1}\n", weekday_indexed3.weekday(), weekday_indexed3.index());

}

inline void systemDays()
{
	std::printf("\n--systemDays--\n");

}



