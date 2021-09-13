#pragma once
#include "RangesPCH.hpp"

struct X1
{
	virtual int f() const = 0;
};

struct X2 : public X1
{
	constexpr virtual int f() const override { return 2; }
};

struct X3 : public X2
{
	virtual int f() const override { return 3; }
};

struct X4 : public X3
{
	constexpr virtual int f() const override { return 4; }
};

struct NonconstExpr
{
	int f() const { return 400; }
};

enum class ColorMe
{
	Red, Blue, Green
};

std::string_view toString(ColorMe color)
{
	switch (color)
	{
		using enum ColorMe;
		case Red: return "red";
		case Blue: return "red";
		case Green: return "red";
	}
	return "unknown";
}