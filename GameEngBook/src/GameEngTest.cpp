#include <stdio.h>
#include "Assertions.h"
#include <iostream>
#include <limits>
#include <bitset>
#include "EndianSwap.h"



int main()
{
	//ASSERT(3 == 5); 
	printf("Test Game Engine BOOK TEST\n");


	std::cout <<std::bitset<32>(255)<< '\n';

	/* Integer Endian SWAP EXAMPLE*/
	Example myExample;

	myExample.m_a = 5;
	myExample.m_b = 2;
	myExample.m_c = 1;

	std::cout << "m_a : " << std::bitset<32>(myExample.m_a)<<'\n';

	myExample.m_a = SwapInt32(myExample.m_a);
	std::cout << "m_a (afterswaped to big endian) : " << std::bitset<32>(myExample.m_a) << '\n';

	/* example for float swapping*/
	U32F32 testval;
	testval.m_asF32 = 35.4f;
	std::cout << "testswap (float) before swapped: " << std::bitset<32>(testval.m_asU32) << '\n';

	testval.m_asF32 = swapF32(testval.m_asF32);
	std::cout << "testswap (float) AFTER swapped: " << std::bitset<32>(testval.m_asU32) << '\n';

	float mynum = 135.4f;
	mynum=swapF32(mynum);

	



}