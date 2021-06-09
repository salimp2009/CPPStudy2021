#pragma once
#include "ConcurrencyPCH.h"

template<typename T>
struct DataGenerator
{
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;

	DataGenerator(handle_type h) : coro{h} {}
	handle_type coro;

	~DataGenerator() { if (coro) { coro.destroy(); } }
	
	DataGenerator(const DataGenerator&) = delete;
	DataGenerator& operator=(const DataGenerator&) = delete;
	
	DataGenerator(DataGenerator&& other) noexcept: coro{std::exchange(other.coro, nullptr)} { }
	DataGenerator& operator=(DataGenerator&& other) noexcept
	{
		coro = std::exchange(other.coro, nullptr);
		return *this;
	}

	T getValue() { return coro.promise().current_value; }

	bool next()
	{
		coro.resume();
		return not coro.done();
	}

	struct promise_type
	{
		promise_type() = default;

		T current_value;
	};

};
