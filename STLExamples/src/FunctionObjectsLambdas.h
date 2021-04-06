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
	MyPerson(std::string n) : name{ std::move(n) } {}

	void printname() const  
	{ 
		fmt::print("MyPerson: {}\n", name); 
	}
	void printname2(std::string&& prefix) const 
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
	
}
