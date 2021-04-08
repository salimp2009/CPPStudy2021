#pragma once

#include "TupplePairUtilities.hpp"
#include "FunctObjLambdaUtils.hpp"




inline void FunctionObjLamb_Test()
{
	fmt::print("\n---------------Function Objects Lambda --------------------------\n");

	std::vector<int> v1{ 1,2 };

	fmt::print("vector print {}", fmt::join(v1,", "));

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
	//++x1;
	lmb2();
	std::cout << "value of x1 after lmb2 mutable changed it: " << x1 << '\n';
	lmb2();
	++x1;
	lmb2();


	/* no need for capturing any gloabal or static variables/objects; if you do you get compiler error*/
	auto lmbd3 = []() noexcept
	{ 
		++gval; ++static_val;
	};

	lmbd3();
	fmt::print("global/static values of gval &static_int after captured/modified in lambda: {0}, {1}\n", gval, static_val);

	Baz bz{ "Salim" };
	auto myBazf1 = bz.foo();
	myBazf1();

	/* this will not print the value of struct member since we create a temp object and 
		by the time we call it expired therefore the value destroyed
	*/
	auto myBazf2 = Baz("Salitos").foo();
	myBazf2();

	std::unique_ptr<int>uptr = std::make_unique<int>(10);

	std::printf("address of uptr: %p \n", uptr.get());
	
	auto ulmd4 = [ptr = std::move(uptr)]() noexcept { fmt::print("ptr in lambda adress {0}, and value {1}\n", fmt::ptr(ptr.get()),*ptr); };
	ulmd4();
	
	std::printf("address of uptr after moved : %p \n", uptr.get());

	std::unique_ptr<int>uptr2 = std::make_unique<int>(10);

	auto Overloadedlambda = Overloader([](auto f) {return f();});
	Overloadedlambda(myBazf1);
	Overloadedlambda(bz.foo());
	
	const int cx = 10;
	/* you cannot modify a captured const variable*/
	auto myconstlmbda= [cx]()mutable {fmt::print("{}\n", std::is_const_v<decltype(cx)>); };
	myconstlmbda();

	/* C++17 version of implementation of variadic capture in lambdas*/
	capture(1, 2, 3, "Salim");

	/* C++20 version of implementation of variadic capture in lambdas*/
#ifdef _HAS_CXX20
	std::string name = "Didem";
	callArgs(1, 2, 3, name);

	std::printf("name after callArgs %s\n", name.c_str());
#endif

	callwith10([](int x) {fmt::print("lambda with 10+ : {}\n", x); });
	callwith10([](int x) {fmt::print("lambda with 10+ : {}\n", x); });

	Bazptr mybaz;
	callwith10(mybaz);
}
