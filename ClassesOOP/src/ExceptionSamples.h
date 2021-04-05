#pragma once

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <exception>


void DivideByZero(double sum, double total)
{
	double average{ 0.0 };
		if( total==0 )throw 0;
	average = sum / total;

}
