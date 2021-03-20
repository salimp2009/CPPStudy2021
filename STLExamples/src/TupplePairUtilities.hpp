#pragma once

#include <iostream>
#include <tuple>



template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
	return os << "[" << p.first << ", " << p.second << "] \n";
}

template<typename... TArgs>
std::ostream& operator<<(std::ostream& os, const std::tuple<TArgs...>& tupleObj)
{
	std::apply([&os](const TArgs...tupleArgs)

		{
			os << '[';
			std::size_t n{ 0 };
			((os << tupleArgs << (++n < sizeof ...(TArgs) ? ", " : "")), ...);
			os << ']' << '\n';
		}, tupleObj);
	return os;
}
