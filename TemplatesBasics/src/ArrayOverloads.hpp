#pragma once

//#include "Templpch.h"

template<typename T>
struct MyClass;

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>
{
	static void print() { fmt::print("print(); for known bounds T[{0}]\n", SZ); }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>
{
	static void print() { fmt::print("print(); for reference to an array; T(&)[{0}]\n", SZ); }
};

template<typename T>
struct MyClass<T[]>
{
	static void print() { fmt::print("print();for unknown size T[]\n"); }
};

template<typename T>
struct MyClass<T(&)[]>
{
	static void print() { fmt::print("print(); for ref to an arrof unknown size; T(&)[]\n"); }
};

template<typename T>
struct MyClass<T*>
{
	static void print() { fmt::print("print(); pointer specialization T*\n"); }
};