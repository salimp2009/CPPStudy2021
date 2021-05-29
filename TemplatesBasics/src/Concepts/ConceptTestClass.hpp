#pragma once
#include "Templpch.h"
#include "Concepts/ConceptsAddAllVers02.hpp"

template<typename... Args>
concept Test = requires
{
	AddAllValues4(std::declval<Args>()...);  // declval will create type with the given type and pass into our function to test
};

/* TODO ; add a type that can create different type so we can pass it above to test it during compile time*/
/* Conditions to test : NOEXCEPT, HASOPERATOR PLUS, HASTYPE, VALIDRETURNTYPE
	the type we will add will have template parameter for above tests 
	so we can pass different template parameter to test different scenarios
*/