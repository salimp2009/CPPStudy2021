#pragma once
#include "RangesPCH.hpp"

template<std::size_t Args>
constexpr auto makeBraces()
{

	constexpr std::array<char, 4>brace{ "{} " };

	// size of brace without string terminator (\0)
	constexpr auto brace_size = brace.size() - 1;

	// reserve 2 characters for newline and string terminator
	constexpr auto offset{ 2u };

	std::array<char, Args* brace_size + offset> totalBraces{};
}
