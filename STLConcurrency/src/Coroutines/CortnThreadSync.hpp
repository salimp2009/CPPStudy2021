#pragma once
#include "ConcurrencyPCH.h"


class Event
{
public:
	Event() = default;
	Event(const Event&) = delete;
	Event(Event&&) = delete;
	Event& operator=(const Event&) = delete;
	Event& operator=(Event&&) = delete;

	class Awaiter;
	Awaiter operator co_await() const noexcept;

	void notify() noexcept;

private:
	friend class Awaiter;
	mutable std::atomic<void*> suspendedWaiter{ nullptr };
	mutable std::atomic<bool> notified{ false };
};

class Event::Awaiter
{
public:
	Awaiter(const Event& eve) : event{ eve } {}
	bool await_ready() const;
	bool await_suspend(std::coroutine_handle<> corHandle) noexcept;
	void await_resume() noexcept {}

private:
	friend class Event;
	const Event& event;
	std::coroutine_handle<> coroutineHandle;
};


bool Event::Awaiter::await_ready() const
{
	// TODO: Check if we can use even.notified.load(std::memory_order_acquire)
	if (event.suspendedWaiter.load() != nullptr)
	{
		throw std::runtime_error("more than one waiter is not valid!!\n");
	}
	// event.notified==false; coroutine is suspended
	// event.notified==true; coroutine is executed like a normal function
	// TODO: Check if we can use even.notified.load(std::memory_order_release)
	return event.notified;
}


void Event::notify() noexcept
{
	//notified.store(true, std::memory_order_release);
	notified = true;
	auto* waiter = static_cast<Awaiter*>(suspendedWaiter.load());

	// if a waiter is available then resume it
	if (waiter != nullptr)
	{
		// this will call await_resume
		waiter->coroutineHandle.resume();
	}
}

bool Event::Awaiter::await_suspend(std::coroutine_handle<> corHandle) noexcept
{
	coroutineHandle = corHandle;

	if (event.notified)
	{
		return false;
	}
	// store the waiter to notify it !
	// TODO; check if this may have std::memory_order_acquire!!
	event.suspendedWaiter.store(this);
	return true;
}


Event::Awaiter Event::operator co_await() const noexcept
{
	return Awaiter{ *this };
}

