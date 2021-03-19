#pragma once
#include <string>
#include <iostream>

class MyString
{
private:
	char* str; //
public:
	MyString();
	MyString(const char* s);
	MyString(const MyString& source);
	MyString(MyString&& source) noexcept;
	~MyString();

	MyString& operator=(const MyString& source)  ;
	MyString& operator=(MyString&& source) noexcept;

	// Lower case conversion
	MyString operator-() const;

	//Overloaded member functions
	MyString operator+(const MyString& rhs) const;
	MyString operator+=(const MyString& rhs);

	void display() const { std::cout << "MyString: " << str << ", length: " << std::strlen(str) << '\n'; }
	size_t  getlength() const { return std::strlen(str); }

	const char* getstr() const { return str; }

	// TODO ; test if this works as move !!!
	char* getstr() { return std::move(str); }

	// TODO; test if it works
	//const MyString& getstr() const& { return str; }
	//MyString&& getstr() && { return std::move(str); }


};

