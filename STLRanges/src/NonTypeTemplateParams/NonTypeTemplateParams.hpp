#pragma once

template<double T>
struct ADouble;


// literal class; a trivial default constexpr destructor, a constexpr constructor, a lambda or aggregate without a constructor
// see all requirements https://en.cppreference.com/w/cpp/named_req/LiteralType
template<typename CharT, std::size_t N>
struct fixed_string
{
	CharT data[N]{};

	constexpr fixed_string(const CharT (&strng)[N])
	{
		//since C++20 copy_n is constexpr
		std::copy_n(strng, N, data);
	}
};

template<fixed_string Str>
void printString()
{
	fmt::print("{}\n", Str.data);
}


template<fixed_string Str>
struct FixedStringContainer
{
	void print()
	{
		fmt::print("{}\n", Str.data);
	}
};

template<fixed_string Str>
struct FormatString
{
	static constexpr auto fmt = Str;
	static constexpr auto numArgs = std::ranges::count(Str.data, '%');
	operator const auto* ()const { return fmt.data; }

};


template<typename... TArgs>
void print(auto formt, const TArgs&... args)
{
	static_assert(formt.numArgs == sizeof...(TArgs));
	std::printf(formt, args...);
}


template<fixed_string Str>
constexpr auto operator"" _fs()
{
	return FormatString<Str>{};
}


template<typename T, typename U>
constexpr bool plain_same_v = std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

template<typename T, typename U>
concept plain_same =plain_same_v<T, U> && plain_same_v<U, T>;

template<typename T>
constexpr static bool match(const char c)
{
	switch (c)
	{
		case 'd': return plain_same_v<int, T>;
		case 'c': return plain_same_v<char, T>;
		case 'f': return plain_same_v<double, T>;
		case 's': return (plain_same_v<char, std::remove_all_extents_t<T>> && std::is_array_v<T>)
					  || (plain_same_v<char*, std::remove_all_extents_t<T>> && std::is_pointer_v<T>) ;
	}

	return false;
}



