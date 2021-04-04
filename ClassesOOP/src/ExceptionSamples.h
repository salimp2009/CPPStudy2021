#pragma once

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <exception>


void DivideByZero(double sum, double total)
{
	double average{ 0.0 };

	try 
	{
		if( total==0 )throw 0;
		average = sum / total;
	}
	catch(int& i) 
	{
		std::cout << " the integer exception was caught, with value: " << i << '\n';
	}


	std::cout << "program continues \n";

}
