#pragma once

// [=] the implicit capture of this is depreciated in c++20 and will probably be removed in c++23;
// so use this to pass the object as pointer or *this as a copy in lambdas inside a class that needs to access member variables
class SomeClass
{
private:
	int value{5};
public:
	int getTwiceValue()
	{
		auto twice = [*this]() { return value * 2; };
		return twice();
	}
};


struct Book
{
	std::string title;
	std::string isbn;
};

struct Price
{
	double amount;
};

auto compare = [](const Book& a, const Book& b) { return a.isbn > b.isbn; };

template<typename VALUE>
using MapBookSortedbyISBN = std::map<Book, VALUE, decltype(compare)>;

struct Magazine
{
	std::string name;
	std::string isbn;
};

template<typename T>
concept HasISBN = requires(T a)
{
	{a.isbn};
};

struct BookNoISBN
{
	std::string title;
	//std::string isbn;
};

auto compareISBN = []<HasISBN T>(T&& a, T&& b) { return a.isbn > b.isbn; };
template<typename KEY, typename VALUE>
using MapSortedbyISBN = std::map<KEY, VALUE, decltype(compareISBN)>;