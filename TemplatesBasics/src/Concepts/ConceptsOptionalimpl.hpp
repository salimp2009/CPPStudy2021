#pragma once
#include "Templpch.h"

/*TODO: this is InComplete*/
template<typename T>
class optional
{
public:
	optional() = default;

	template<typename U, typename =std::enable_if_t<std::is_same_v<U, optional> && std::is_copy_constructible_v<T>>>
	optional(const U&);

private:
	std::aligned_storage_t<sizeof(T), alignof(T)> value;
};


std::optional<int> opt1;
