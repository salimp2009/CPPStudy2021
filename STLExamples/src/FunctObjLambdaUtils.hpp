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

/*C17 version of capturing */
template<typename... Args>
constexpr void capture(Args&&... args) noexcept
{
	auto captlambda = [args...]()noexcept
	{
		const auto tup = std::make_tuple(args...);
		fmt::print("tupple size: {0}, sizeof args: {1}, sizeof(Args): {2}\n", std::tuple_size_v<decltype(tup)>, sizeof... (args), sizeof... (Args));
		(fmt::print("{} ", args), ...);
		/*Alternative way of printing; might work containers in fmt*/
		fmt::print("\n{} \n", tup);
		
	};
	captlambda();
}

/*C20 version of above; capture variadics in lambdas*/
#ifdef _HAS_CXX20
	template<typename...Args>
	constexpr void callArgs(Args&&... args) noexcept
	{
		auto captC20vers = [...captargs = std::forward<Args>(args)]() noexcept
		{
			(fmt::print("{} ", captargs), ...);
			std::printf("\n");
		};
		captC20vers();
	}
#endif

	inline void callwith10(void(*func)(int)) noexcept { static int n= 10; func(++n); };

	struct Bazptr
	{
		using f_ptr = void(*)(int);

		void operator()(int s) const noexcept { return call(s); };

		/*conver to function pointer that takes an int return void and return the address of call function*/
		operator f_ptr() const noexcept { return &call; }
	private:
		static void call(int n)  { fmt::print("Bazptr calls: {}\n", n); }
	};

	
