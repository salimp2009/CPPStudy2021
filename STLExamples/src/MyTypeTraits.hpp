#pragma once
#include <iostream>
#include <type_traits>

template<typename T>
decltype(auto) TypeFoo(const T& val)
{
	if constexpr (std::is_same_v<T, std::unique_ptr<int>>)
	{
		std::cout << "foo() called with a pointer \n";
	}
		
	else
	{
		std::cout << "foo() called with a value \n";
	}
		
}


