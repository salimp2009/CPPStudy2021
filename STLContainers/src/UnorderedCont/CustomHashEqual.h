#pragma once

#include "OverLoadVariadic.hpp"

class Customer
{
private:
	std::string fname;
	std::string lname;
	long no;
public:
	Customer(std::string fn, std::string ln, long n) : fname{ std::move(fn) }, lname{ std::move(ln) }, no{ n } {}

	const std::string& GetFName() const& { return fname; }
	std::string GetFName()&& { return std::move(fname); }


	const std::string& GetLName() const& { return lname; }
	std::string GetLName()&& { return std::move(lname); }

	long GetNo() { return no; }
	long GetNo() const { return no; }
	


	friend std::ostream& operator<<(std::ostream& os, const Customer& c)
	{
		return os <<"["<< c.fname << ", " << c.lname << ", " << c.no << "]";
	}

	friend class CustomerEqual;
	friend class CustomerHash;
	
};

class CustomerEqual
{
public:
	bool  operator()(const Customer& c1, const Customer& c2) const noexcept
	{
		return c1.no == c2.no;
	}
};


class CustomerHash
{
public:
	std::size_t operator()(const Customer& c1) const noexcept
	{
		return std::hash<std::string_view>{}(c1.fname) ^ (std::hash<std::string_view>{}(c1.lname)<<1) + (std::hash<long>{}(c1.no)>>2);
	}

};