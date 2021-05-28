#pragma once
#include "Templpch.h"

/* Before Concepts*/
template<typename T, typename U>
constexpr bool IsSameTypeOLD = std::is_same_v<T, U>;

/* With Concepts!*/
template<typename T, typename U>
concept IsSameType = std::is_same_v<T, U>;

/* Before concepts*/
template<typename T, typename... Ts>
inline constexpr bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

/* Before concepts*/
template<typename T, typename... Args>
constexpr auto  addValues(T&& arg, Args&&...args)->std::enable_if_t<are_same_v<T, Args...>, T>
{
	
	return (arg + ... + args);
}

/* With concepts*/
template<typename T, typename... Ts>
concept same_values = std::conjunction_v<std::is_same<T, Ts>...>; 

template<typename T, typename... Args>
requires same_values<T, Args...>
constexpr auto addAllValues(T&& arg, Args&&...args)
{
	return (arg + ... + args);
}


template<typename T>
concept ByteLikeType = std::same_as<void*, T> || std::same_as<char*, T> || std::same_as<unsigned char*, T>
					|| std::same_as<const void*, T> || std::same_as<const char*, T> || std::same_as<const unsigned char*, T>;


/* incomplete !!!!*/
template<typename T, typename...Args>
concept variadic_Sumable = requires(T arg)
{
	(arg + arg);									// check if args provides + operator
	requires are_same_v<T, Args...>;
	//requires same_values<T, Args...>;
	requires sizeof...(Args) >0;					// at least one parameter

	{(arg + arg) } noexcept ->std::same_as<T>;		// check if the sum returns a type equal to first parameter T
	typename T::type;								// the return type injected as the second parameter in same_As

};