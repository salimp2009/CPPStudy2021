#include <cstdio>
#include "spdlog/fmt/fmt.h"
#include <vector>

import math;


int main()
{
	std::printf("HEllo from main\n");
	
	std::printf("test mathh module; add(): %d\n", add(10, 20));
	fmt::print("test mathh module; add(): {0}\n", add(10, 20));

	auto var =add(15, 20);
	fmt::print("test math module; add(): {0}\n", var);

	std::vector<int> myvec{ 1,2,3 };

	/* intellisense */
	fmt::print("getproduct: {}\n", getProductNew(myvec));
}