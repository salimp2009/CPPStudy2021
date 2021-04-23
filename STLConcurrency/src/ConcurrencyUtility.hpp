#pragma once

#ifdef NDEBUG
	#define ASSERTM(exp, msg) assert ((void)0)
#else
	#define	ASSERTM(exp, msg) assert(((void)msg, exp))
#endif

/*---std::cout overloaded for Pair---*/
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
	return os << "[" << p.first << ", " << p.second << "] \n";
}

/*---std::cout overloaded for Tupple---*/
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


template<typename Cont>
constexpr void printCont(Cont& cont)
{
	if (cont.empty()) return;

	for (auto&& elem : cont)
	{
		fmt::print("{} ", elem);
	}
	fmt::print("\n");
}

