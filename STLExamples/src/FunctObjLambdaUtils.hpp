#pragma once

/* Global and Static variables/objects to test Lambda Captures*/
int gval = 10;
static int static_val = 15;

template<class... Bases>
struct Overloader : Bases...
{
	using Bases::operator()... ;
};

template<class... Bases>Overloader(Bases...)->Overloader<Bases...>;


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
	PrinterEx() noexcept :numCalls{ 0 } {}

	void operator()(int x) noexcept
	{
		fmt::print("{} ", x);
		fmt::print("\n");
		++numCalls;
	}
};


struct Baz
{
	decltype(auto) foo() noexcept
	{
		return [this]() noexcept{ fmt::print("value of member s: {0}\n", s); };
	}

	std::string s;
};