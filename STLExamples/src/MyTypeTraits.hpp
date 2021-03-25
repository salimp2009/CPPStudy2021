#pragma once
#include "STLpch.h"

//#include <iostream>
//#include <type_traits>

template<typename T>
void TypeFoo(T&& val)
{
	if (std::is_pointer_v<std::decay_t<decltype(val)>>)
	{
		std::cout << "foo() called with a pointer \n";
	}
	else
	{
		std::cout << "foo() called with a value \n";
	}
}

template <typename T>
constexpr void TypeFoo2(const T& val)
{
	if constexpr (std::is_pointer<T>::value)
	{
		std::cout << *val << '\n';
	}
	else
	{
		std::cout << val << '\n';
	}
}


