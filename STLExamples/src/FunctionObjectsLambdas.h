#pragma once

#include "TupplePairUtilities.hpp"
#include "FunctObjLambdaUtils.hpp"

#define FUNCTWRAP(fn)\
[](auto&&... x)\
	noexcept(noexcept(fn(std::forward<decltype(x)>(x)...)))\
	->decltype(fn(std::forward<decltype(x)>(x)...))\
	{return fn(std::forward<decltype(x)>(x)...);}


inline void FunctionObjLamb_Test()
{
	fmt::print("\n---------------Function Objects Lambda --------------------------\n");

	std::vector<int> v1{ 1,2 };

	fmt::print("vector print {}", fmt::join(v1, ", "));

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
	std::cout << plus10times2(7) << '\n';

	std::mem_fn(&MyPerson::printname)(MyPerson("Salim"));
	std::mem_fn(&MyPerson::printname2)(MyPerson("Didem"), "is a ");

	int x1 = 5;
	auto l1 = [&x1]() mutable noexcept { fmt::print("x1 from lambda thru a : {} \n", ++(x1)); };
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

	auto ulmd4 = [ptr = std::move(uptr)]() noexcept { fmt::print("ptr in lambda adress {0}, and value {1}\n", fmt::ptr(ptr.get()), *ptr); };
	ulmd4();

	std::printf("address of uptr after moved : %p \n", uptr.get());

	std::unique_ptr<int>uptr2 = std::make_unique<int>(10);

	auto Overloadedlambda = Overloader([](auto f) {return f(); });
	Overloadedlambda(myBazf1);
	Overloadedlambda(bz.foo());

	const int cx = 10;
	/* you cannot modify a captured const variable*/
	auto myconstlmbda = [cx]()mutable {fmt::print("{}\n", std::is_const_v<decltype(cx)>); };
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

	auto funcptr = static_cast<void(*)()>([]()->decltype(auto) {});
	static_assert(std::is_same_v<decltype(funcptr), void(*)()>);

	/*Example for passing lamda into container stateless*/
	using TFunct = void(*)(int&);
	std::vector<TFunct> ptrFunctVec;
	
	ptrFunctVec.emplace_back([](int& x) {fmt::print("x: {}\n", x); });
	ptrFunctVec.emplace_back([](int& x) {x *= 2; });
	ptrFunctVec.emplace_back(ptrFunctVec[0]);

	int vx = 10;
	for (const auto& elem : ptrFunctVec)
	{
		elem(vx);
	}
	

}

inline void FunctionObjLamb_Test2()
{
	std::printf("\n---------------Function Objects Lambda Part2--------------------------\n");

	auto lam1 = [](int x = 10) {fmt::print("x: {}\n", x); };
	lam1();

	int x1 = 15;
	auto lam2 = [&z = x1]() {fmt::print("z: {}\n", z); };
	lam2();
	x1 = 35;
	lam2();

	std::unique_ptr<int>uptr(new int(10));

	std::function<void()>ufunct = [ptr = &uptr]{};

	using namespace std::string_literals;
	/* vector is used for example but prefer std::Array if const is used */
	const std::vector<std::string>vs = { "Salim"s, "Didem", "foobar"s, "Demir"s };

	const auto prefix = "foo"s;
	auto result = std::find_if(vs.cbegin(), vs.cend(), 
					[searchprefix = prefix + "bar"s](std::string_view elem) { return elem == searchprefix; });

	if (result != vs.cend())
	{
		fmt::print("result: {}", *result);
	}

	const auto myf2 = Baz{ "c++" }.foo2();
	myf2();

	const auto sumLambda = [](auto&&... args)
	{
		fmt::print("sum of {} numbers: ", sizeof... (args));
		return sumFold(std::forward<decltype(args)>(args)...);
	};

	fmt::print("{} \n", sumLambda(1, 2.1, 3.1f, 4.1));

	/** Example to check the when using auto && there is no extra copies by checking the values address in container
		and comparing in the std::for_each and passing into lambda
	*/
	const std::map<std::string, int>numbers = { {"one", 1}, {"two", 2}, {"three",3} };

	for (auto it = numbers.cbegin(); it != numbers.end(); ++it)
	{
		fmt::print("{0}, {1} \n", fmt::ptr(&(it->first)), fmt::ptr(&(it->second)));
	}

	std::for_each(numbers.cbegin(), numbers.cend(),
		[](auto&& elem) 
		{
			fmt::print("{0}, {1} \n", fmt::ptr(&(elem.first)), fmt::ptr(&(elem.second)));	
		});

	const std::array<int, 10> arr1={ 1,2,3,4,5,6,7,8,9 };

	/* Will not compile since fooFI overloads cannot be deduced */
	//std::for_each(arr1.begin(), arr1.end(), fooFI);

	std::for_each(arr1.begin(), arr1.end(), [](auto&& x) noexcept(noexcept(fooFI(std::forward<decltype(x)>(x)))) ->decltype(auto) { return fooFI(std::forward<decltype(x)>(x)); });
	std::printf("\n");
	
	/* More generic lambda version of the above within a Macro */
	std::for_each(arr1.begin(), arr1.end(), FUNCTWRAP(fooFI));
	std::printf("\n");

	constexpr auto factorialLambd = [](auto&& n) constexpr noexcept
	{
		constexpr auto factor_impl = [](auto&& n, const auto& impl) constexpr noexcept->int
		{return n > 1 ? n * impl(n - 1, impl) : 1; };
		
		return factor_impl(n, factor_impl);
	
	};

	const int n = 5;
	fmt::print("factorial of {1}: {0}\n",factorialLambd(n), n);

}