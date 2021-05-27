#pragma once
#include "Templpch.h"

/* Before Concepts*/
template<typename T, typename U>
constexpr bool IsSameTypeOLD = std::is_same_v<T, U>;

/* With Concepts!*/
template<typename T, typename U>
concept IsSameType = std::is_same_v<T, U>;
