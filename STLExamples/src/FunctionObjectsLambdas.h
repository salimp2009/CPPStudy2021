#pragma once

#include "TupplePairUtilities.hpp"

class IntSequence
{
private:
	int value;
public:
	constexpr IntSequence(int val) noexcept :value{ val } {}

	constexpr int operator()() noexcept
	{
		return value++;
	}

};

class MyPerson
{
private:
	std::string name;
public:
	MyPerson(std::string n) noexcept : name{ std::move(n) } {}

	void printname() const noexcept 
	{ 
		fmt::print("MyPerson: {}\n", name); 
	}
	void printname2(std::string&& prefix) const noexcept
	{ 
		fmt::print("MyPerson: {0} {1} \n", std::move(prefix), name); 
	}

};

struct PrinterEx
{
	int numCalls;
	PrinterEx() noexcept:numCalls{0}{}

	void operator()(int x) noexcept
	{
		fmt::print("{} ", x);
		fmt::print("\n");
		++numCalls;
	}
};

/* Global and Static variables/objects to test Lambda Captures*/
int gval = 10;
static int static_val = 15;

inline void FunctionObjLamb_Test()
{
	fmt::print("\n---------------Function Objects Lambda --------------------------\n");

	
	std::vector<int> v1{ 1,2 };

	const PrinterEx vis = std::for_each(v1.begin(), v1.end(), PrinterEx());
	
	fmt::print("numcalls: {}\n", vis.numCalls);
	
	std::list<int>coll;
	IntSequence seq(1);

	std::generate_n<std::back_insert_iterator<std::list<int>>, int, IntSequence&>(std::back_inserter(coll), 4, seq);
	printCont(coll);

	std::generate_n(std::back_inserter(coll), 4, seq);
	printCont(coll);

	std::generate_n(std::back_inserter(coll), 4, seq);
	printCont(coll);

	std::generate_n(std::back_inserter(coll), 2, IntSequence(44));
	printCont(coll);

	auto plus10times2 = [](auto&& y) {return (y + 10) * 2; };
	std::cout<< plus10times2(7)<<'\n';

	std::mem_fn(&MyPerson::printname)(MyPerson("Salim"));
	std::mem_fn(&MyPerson::printname2)(MyPerson("Didem"), "is a ");

	int x1 = 5;
	auto l1 = [&x1]() mutable noexcept { fmt::print("x1 from lambda thru a : {} \n",++(x1)); };
	x1 = 456;
	l1();

	auto lmb2 = [x1]() mutable noexcept 
	{ 
		fmt::print("x1 from lmb2 copied by val (mutable) {}\n", ++x1); 
		
	};

	lmb2();
	std::cout << "value of x1 after lmb2 mutable changed it: " << x1 << '\n';
	++x1;
	lmb2();
	std::cout << "value of x1 after lmb2 mutable changed it: " << x1 << '\n';

	/* no need for capturing any gloabal or static variables/objects; if you do you get compiler error*/
	auto lmbd3 = []() noexcept
	{ 
		++gval; ++static_val;
	};

	lmbd3();
	fmt::print("global/static values of gval &static_int after captured/modified in lambda: {0}, {1}\n", gval, static_val);

}
