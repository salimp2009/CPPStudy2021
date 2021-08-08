#pragma once
#include "RangesPCH.hpp"
#include "LambdaImprovements.hpp"


inline void LambdaCapturesInClass()
{
	std::printf("\n-LambdaCapturesInClass-\n");

	SomeClass somecls1;
	fmt::print("{}", somecls1.getTwiceValue());
}

inline void DefaultConstructibleLambdas()
{
	std::printf("\n-DefaultConstructibleLambdas-\n");

	const Book effectiveCpp{ "Effective C++", "978-3-16-148410-0" };
	const Book functProgCpp{"Functional Programming in C++", "978-3-20-148410-0"};

	const Price normal{ 34.95 };
	const Price reduced{ 24.95 };

	// After C++20
	MapBookSortedbyISBN<Price> book2Price{ {effectiveCpp, normal}, {functProgCpp, reduced} };

	// Before C++20; gives compiler error if compiled with C++20 ; OK if compiled with C++17
	// MapBookSortedbyISBN<Price> book3Price( {effectiveCpp, normal}, {functProgCpp, reduced}, compare );
	for (const auto& [book, price] : book2Price)
	{
		fmt::print("book name: {}, ISBN: {}, Price: {}\n", book.title, book.isbn, price.amount);
	}
}

