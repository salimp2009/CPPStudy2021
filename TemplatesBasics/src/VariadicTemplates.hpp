#pragma once
#include "Templpch.h"

void printVar() {}

template<typename TFirst, typename... Types>
void printVar(TFirst firstArg, Types... args)
{
	auto size = sizeof...(args);
	fmt::print("{0}{1}", firstArg, (size-->0 ? ", ": "\n"));
	
	if constexpr (sizeof...(args)>0)
	{
		printVar(args...);
	}
}

template<typename T>
void printVar2(T&& arg) 
{
	fmt::print("{0} ", arg);
}

template<typename TFirst, typename... Types>
void printVar2(TFirst&& firstArg, Types&&... args)
{
	printVar2(std::forward<TFirst>(firstArg));
	printVar2(std::forward<Types>(args)...);
}

template<typename... T>
decltype(auto) foldSum(T... args)
{
	return (... + args); // Equal to ((s1+s2)+s3)  // left fold;
}

template<typename... T>
decltype(auto) foldSumWithInit(T... args)
{
	return (sizeof...(args) + ... + args); // Equal to ((s1+s2)+s3)  // left fold;
}

void inline VariadicTemplate_Basics()
{
	printVar(7.5, "Hello variadics", "c++", 200);
	printVar2(7.5, "Hello variadics", "c++", 200);
	std::printf("\n");
	printVar2(35, 45, "jaws", 200);
	std::cout << "what the ff....";
	fmt::print("\nfold sum: {}", foldSum(1, 2, 3, 4, 5.5f));
	fmt::print("\nfold sum: {}", foldSumWithInit(1, 2, 3, 4));



}
