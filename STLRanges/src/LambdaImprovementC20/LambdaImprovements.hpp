#pragma once

class SomeClass
{
private:
	int value{5};
public:
	int getTwiceValue()
	{
		auto twice = [=]() { return value * 2; };
		return twice();
	}
};
