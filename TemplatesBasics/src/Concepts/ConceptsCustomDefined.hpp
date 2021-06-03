#pragma once

#include "Templpch.h"

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept SignedIntegral = Integral<T> && std::is_signed_v<T>;

template<typename T>
concept UnSignedIntegral = Integral<T> && !SignedIntegral<T>;

template<typename T>
concept ArithmeticType = std::is_integral_v<T> || std::is_floating_point_v<T>;

inline void funct(UnSignedIntegral auto integ)
{
	fmt::print(" UnsignedIntegral: {}\n", integ);
}

inline void funct(SignedIntegral auto integ)
{
	fmt::print(" SignedIntegral: {}\n", integ);

}
