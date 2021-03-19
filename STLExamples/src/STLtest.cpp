#include <stdio.h>
#include <utility>
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <tuple>
#include <string>
#include <complex>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
	return os <<"["<<p.first << ", " << p.second <<"] \n";
}

typedef std::pair<int, float> IntFloatPair;

class Foo
{
public:
	Foo(std::tuple<int, float>) { std::cout << "Constructed Foo from a tuple\n"; };

	Foo(int a, float b) { std::cout << "Constructed Foo from an int and float \n"; };

	
};

void PairTest()
{
	std::tuple<int, float> t{ 42, 50.25f };
	std::pair<Foo, Foo> p4{ t,t };
	std::pair<Foo, Foo> p5{ std::piecewise_construct,  t, t };

	std::pair<int, float> p6{ 4, 20.3f };
	int c = 20;
	std::tie(c, std::ignore) = p6; // ties the first arg of p6 into c by reference so c changes; Changing c does not change P6
	std::cout << "c: " << c << '\n';



	auto& [u, v] = p6;
	std::cout << "u: " << u << ", v: " << v << '\n';

	auto pair1 = std::make_pair(20, "Salim");
	std::cout << pair1 << '\n';

	IntFloatPair p2(20, 40.5f);
	std::cout << p2 << '\n';

	std::cout << std::get<0>(p2) << '\n';

	std::cout << std::tuple_size<IntFloatPair>::value << '\n';
	std::cout << typeid(std::tuple_element<1, IntFloatPair>::type).name() << '\n';
	std::cout << std::boolalpha;
	std::cout << std::is_same_v<std::tuple_element<1, IntFloatPair>::type, float> << '\n'; // expected true
	static_assert(std::is_same_v<std::tuple_element<1, IntFloatPair>::type, float>, "Pair.second element must be a float");
	std::cout << std::is_same_v<decltype(p2.first), float> << '\n';   // expected false

}


void TupleTest()
{
	std::tuple<int, float, std::string> t1{ 2, 23.4f, "Salim" };

	std::cout << "\n----------------------Tuples Test ------------------------------------\n";
	std::cout << get<0>(t1) << '\n';
	std::cout << get<1>(t1) << '\n';
	std::cout << get<2>(t1) << '\n';

	std::cout << "\n----------------------Tuples Test ------------------------------------\n";
}


int main()
{
	//PairTest();

	TupleTest();


	return 0;
}



