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
		~promise_type() = default;

		auto initial_suspend()        { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }

		auto get_return_object() { return DataGenerator{ handle_type::from_promise(*this) }; }
		auto return_void()		 { return std::suspend_never{}; }

		auto yield_value(const T& value)
		{
			current_value = value;
			return std::suspend_always{};
		}

		void unhandled_exception() { std::exit(1); }

		T current_value;
	};
};


inline DataGenerator<int> getNextData(int start = 0, int step = 1)
{
	auto value = start;
	while (true)
	{
		co_yield value;
		value += step;
	}
}


