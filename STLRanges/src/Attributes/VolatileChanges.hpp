#pragma once
#include "RangesPCH.hpp"

// Depreciated cases for volatile

int neck, tail;
volatile int dinasor;

struct amber {};

// depreciated volatile use in c++20; MSVC gives no warning
volatile struct amber jurassic() { return {}; }
	
// data is volatile ; not the pointer
void fly(volatile struct pretausorious* dynos) { }

// depreciated volatile use in functions; MSVC gives no warning!!
void trex(volatile short leftarm, volatile short rightarm) {}


