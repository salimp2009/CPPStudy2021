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
	fmt::print("{}", Str.data);
}
