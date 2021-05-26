
#include <cstdio>
#include <vector>

#include "spdlog/fmt/fmt.h"


import math;


int main()
{
	std::printf("test mathh module; add(): %d\n", math::add(10, 20));
	//fmt::print("test mathh module; add(): {0}\n", add(10, 20));

	auto var =math::add(15, 20);
	fmt::print("test math module; add(): {0}\n", var);

	std::vector<int> vec1{ 1,2,3 };

	/* intellisense gives red squigless ; false error but it works???*/
	fmt::print("getproduct: {}\n", math::getProduct(vec1));

	auto var2 = math::getProduct(vec1);
	std::printf("test math module; getproduct(): %d\n", math::getProduct(vec1));
}