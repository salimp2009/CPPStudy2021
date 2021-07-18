#pragma once
#include "RangesPCH.hpp"
#include <type_traits>

enum LogLevel {Info, Warning, Error};

template<>
struct std::formatter<LogLevel> :std::formatter<std::string_view>
{
	static constexpr const char* LEVEL_NAMES[] = {"Info", "Warning", "Error"};

	auto format(LogLevel c, std::format_context& ctx)
	{
		return std::formatter<std::string_view>::format(LEVEL_NAMES[(c)], ctx);
	}
};

// TODO: make a revised version of this to used std::format_args and std::make_format_args and std::vformat for Args... //
// othervise std::format will create a seperatea new log function will be called causing a larger binary
// std::vformat is non-template version of std::format
template<typename... Args>
void custLoggger(LogLevel level, std::string_view fmt, Args&&... args)
{
	fmt::print("{} {} \n", std::format("{}!!", level), std::format(fmt, std::forward<Args>(args)...));
}

