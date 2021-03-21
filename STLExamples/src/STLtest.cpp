#include <stdio.h>
#include "TupplePairUtilities.hpp"
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <string>
#include <vector>


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

	std::cout <<"\t tuple print utility test: "<< t1 << '\n';


	std::tuple<int, float, std::string> t2 = std::make_tuple(2, 23.4f, "Didem");

	std::cout << std::boolalpha;
	std::cout << (t1 < t2) << '\n';

	std::cout << std::tuple_size<decltype(t2)>::value << '\n';
	std::cout << typeid(std::tuple_element<1, decltype(t2)>::type).name() << '\n';

	std::tuple<int, double> t3 = { 2, 45.6 };
	std::cout << t3 << '\n';

	std::cout << "\n----------------------Tuples Test ------------------------------------\n";
}

void SmartPointers_Test()
{
	std::printf ("\n----------------------Smart Pointers------------------------------------\n\n");
	
	std::shared_ptr<std::string> ps1{ new std::string("Salim") };
	/* faster one allocation instead of 2 ; shared_ptr uses two object; one counter and the pointer/value */
	std::shared_ptr<std::string> ps2 = std::make_shared<std::string>("Didem"); 

	std::cout <<"ps1: "<< *ps1 << '\n';
	std::printf("ps2: %s \n", (*ps2).c_str());

	(*ps1)[0] = 'D';
	ps1->replace(1, 1, "A");
	std::cout <<"ps1 modified: "<< *ps1 << '\n';

	using ShrdPtr = std::shared_ptr<std::string>;

	std::vector<ShrdPtr> NameList;
	NameList.push_back(ps1);
	NameList.emplace_back(std::move(ps2));


	std::cout << "NameList: ";
	for (auto&& names : NameList)
	{
		std::cout << *names << " ";
		std::cout << '\n';
	}

	std::cout << "Use count of ps1: " << *NameList[0] <<", use count: "<< NameList[0].use_count() << '\n';

	std::cout << "Use count of ps2: " << *NameList[1] << ", use count: " << NameList[1].use_count() << '\n';

	std::printf("\n----------------------Smart Pointers------------------------------------\n");
}


int main()
{
	//PairTest();

	//TupleTest();
	SmartPointers_Test();

	

	return 0;
}



