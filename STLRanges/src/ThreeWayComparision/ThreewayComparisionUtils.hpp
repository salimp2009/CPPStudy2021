#pragma once
#include "RangesPCH.hpp"


struct MyInt
{
	int value;
	explicit MyInt(int val) : value{ val } {}
	bool  operator==(const MyInt&) const = default;
	auto operator<=>(const MyInt& rhs) const { return value <=> rhs.value; }
};

struct MyDouble
{
	double value;
	explicit constexpr MyDouble(double val) : value{ val } {}
	auto  operator<=>(const MyDouble&) const = default;
};

struct VectorPointer
{
	std::vector<int>* pointertoVector;
	auto operator<=>(const VectorPointer&) const = default;
};



class String
{
public:
	template<std::size_t N>
	explicit String(const char(&src)[N]) : mData{ src }, mLen{ N } {}

	const char* begin() const { return mData; }
	const char* end() const { return mData + mLen; }

	auto operator<=>(const String& other) const
	{
		return Compare(*this, other);
	}

	bool operator==(const String& other)
	{
		if (mLen != other.mLen) { return false; }
		return Compare(*this, other)==0;
	}

private:
	const char* mData;
	std::size_t mLen;

	static std::weak_ordering Compare(const String& a, const String& b);
};


std::weak_ordering String::Compare(const String& a, const String& b)
{
	
		if (a.mLen == b.mLen &&
			std::equal(a.begin(), a.end(), b.begin(), b.end())) {
			return std::weak_ordering::equivalent;
		}

		// lex_compare uses less<> funct by default so if it is true, a<b==true
		if (std::lexicographical_compare(
			a.begin(), a.end(), b.begin(), b.end())) {
			return	std::weak_ordering::less;				
		}

		return std::weak_ordering::greater;

}
