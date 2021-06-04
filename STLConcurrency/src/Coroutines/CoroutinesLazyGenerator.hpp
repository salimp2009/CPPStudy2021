#pragma once
#include "ConcurrencyPCH.h"



template<typename T, typename G>
struct promise_type_base
{
	/* value yielded from a coroutine*/
	T mValue;

	/* invoked by co_yield or co_return*/
	auto yield_value(T value)
	{
		/* storing the value for access*/
		mValue = std::move(value);
		/* Suspend the coroutine*/
		return std::suspend_always{};
	}

	G get_return_object() { return G{ this }; }

	// TODO : add more functions!!

};

namespace coro_iterator
{
	template<typename PT>
	struct iterator {};


} // end of namespace coroiterator



template<typename T>
struct generator
{
	/* The promise type*/
	using promise_type = promise_type_base <T, generator>;
	using PromiseTypeHandle = std::coroutine_handle<promise_type>;

	/* Make generator iterable*/
	using iterator = coro_iterator::iterator<promise_type>;
	iterator begin() { return { mCoroHd1 }; }
	iterator end() { return {}; }

	generator(const generator&) = delete;
	generator(generator&& rhs) : mCoroHd1( std::exchange(rhs.mCoroHd1, nullptr) ) {}

	~generator()
	{
		/* Coroutine handle keeps a pointer to state of coroutine 
		  therefore if it is not null it should be destroyed 
		  in the destructor of the generator*/
		if (mCoroHd1) mCoroHd1.destroy();
	}


private:
	/* promise_type constructor is private therefore to access we need to friend it*/
	friend promise_type;

	explicit generator(promise_type* p) : mCoroHd1{ PromiseTypeHandle::from_promise(*p) } {}


	/* Coroutine handle; TODO: change the name to mCoroHandle1; more clear!!*/
	PromiseTypeHandle mCoroHd1;
};


