#pragma once
#include "ConcurrencyPCH.h"



template<typename T, typename G>
struct promise_type_base;

template<typename T>
struct generator
{
	using promise_type = promise_type_base <T, generator>;
	using PromiseTypeHandle = std::coroutine_handle<promise_type>;

	using iterator = coro_iterator::iterator<promise_type>;

};


namespace coro_iterator
{
	template<typename PT>
	struct iterator {};


}