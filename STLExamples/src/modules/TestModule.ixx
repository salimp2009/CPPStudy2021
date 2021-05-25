#include "STLpch.h"

export module TestModule;


int mymoduleVariable = 500;

export int MyModuleFunc(int n)
{
	return n+mymoduleVariable;
}
