#include <stdio.h>
#include "TupplePairUtilities.hpp"
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <string>
#include <vector>
#include "Person.h"


typedef std::pair<int, float> IntFloatPair;

struct X
{
	int a = 1;
};


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

	/* Compiles as of c++17; does not works work before c++17*/
	/* custom deleters can be used ; if not used since c++17 default deleter also call delete[]p */
	std::shared_ptr<int[]> ps3(new int[10], [](int* p) { std::cout << "custom deleter\n"; delete[]p; });
	std::shared_ptr<int[]> ps4 = std::make_shared<int[10]>();

	ps3[0] = 1;
	ps3[1] = 2;
	std::cout << ps3[1] << '\n';


	/* DONT THIS ANYMORE; Before C++17; older version*/
	std::shared_ptr<int>ps5(new int[10]{ 1,2,3,4,5 }, [](int* p) { std::cout << "Old style shared ptr w/ array\n"; delete[] p; });
	*ps5 = 10;
	(ps5.get())[1] = 20;
	std::cout << *ps5 << (ps5.get())[4]<< '\n';

	std::printf("\n----------------------Smart Pointers------------------------------------\n");
}

void WeakPointers_Test()
{
	std::printf("\n----------------------Weak Pointers------------------------------------\n\n");
	
	std::shared_ptr<Person> p1 = InitFamily("salim");
	std::cout << "salim's family exist!!!!\n";
	std::cout << "- salim is shared " << p1.use_count() << " times\n";

	/* Make sure the the shared pointer that weak_ptr is pointing still exist otherwise we will get a nullptr*/
	/*Alternative is to check if p1->mother->kids[0].lock() */
	if (!p1->mother->kids[0].expired())
	{
		std::cout << "- name of 1st kid of salim's mom: " << p1->mother->kids[0].lock()->name << '\n';
	}

	p1 = InitFamily("didem");
	std::cout << "Didem's family exist!!!!\n";
	std::cout << "p1 use count: " << p1.use_count() << '\n';

	/**In order to increase life time of object we first create an shared_ptr
	 then we create a ptr to one if it is members so that when the object goes out of scope 
	 the first shared_ptr will hold it ; known as "Aliasing Constructor" 
	 */
	std::shared_ptr<X> xp(new X);
	std::shared_ptr<int> pa(xp, &xp->a);

	std::cout <<"a of Struct X by pa: "<< *pa << '\n';

	std::printf("\n----------------------Weak Pointers------------------------------------\n\n");
}



int main()
{
	//PairTest();

	//TupleTest();
	//SmartPointers_Test();
	WeakPointers_Test();
	

	return 0;
}



