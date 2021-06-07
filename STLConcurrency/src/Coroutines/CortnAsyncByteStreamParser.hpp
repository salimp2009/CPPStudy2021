#pragma once
#include "ConcurrencyPCH.h"

// TODO: InComplete!!!

#define INCOMPLETE 1

#if INCOMPLETE
namespace AsyncParse
{
	template<typename T, typename G, typename... Bases>
	struct promise_type_base: public Bases...
	{
		/* value yielded from a coroutine*/
		T mValue;

		/* invoked by co_yield or co_return*/
		auto yield_value(T value)
		{
			mValue = value;
			return std::suspend_always{};
		}

		/*return the generator*/
		G get_return_object() { return G{ this }; }

		std::suspend_always initial_suspend()		 { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void				return_void() {}
		void				unhandled_exception() { std::terminate(); }
	};

	template<typename T>
	struct awaitable_promise_type_base
	{
		std::optional<T> mRecentSignal;

		struct awaiter
		{
			std::optional<T>& mRecentSignal;

			bool await_ready() { return mRecentSignal.has_value(); }
			void await_suspend(std::coroutine_handle<>) { }

			T await_resume()
			{
				assert(mRecentSignal.has_value());
				auto tmp = *mRecentSignal;
				mRecentSignal.reset();
				return tmp;
			}
		};

		[[nodiscard]] awaiter await_transform(T) { return awaiter{ mRecentSignal }; }
	};


	template<typename T, typename U>
	struct [[nodiscard]] async_generator
	{
		using promise_type = promise_type_base<T, async_generator, awaitable_promise_type_base<U> >;
		using PromiseTypeHandle = std::coroutine_handle<promise_type>;

		T operator()()
		{
			// move clears the value of promise but leave it undefined state
			auto tmp{ std::move(mCoroHd1.promise().mValue()) };
			// set the promise to a defined state
			mCoroHd1.promise().mValue.clear();

			return tmp;
		}

		void SendSignal(U signal)
		{
			mCoroHd1.promise().mRecentSignal = signal;
			if (not mCoroHd1.done()) { mCoroHd1.resume(); }
		}

		async_generator(const async_generator&) = delete;
		async_generator(async_generator&& rhs) : mCoroHd1{ std::exchange(rhs.mCoroHd1, nullptr) } {}

		~async_generator() { if (mCoroHd1) mCoroHd1.destroy(); }

	private:
		friend promise_type;
		explicit async_generator(promise_type* p) : mCoroHd1(PromiseTypeHandle::from_promise(*p)) {}

		PromiseTypeHandle mCoroHd1;
	};

	using FSM = async_generator<std::string, std::byte>;

	FSM Parse()
	{
		while (true)
		{
			std::byte bb = co_await std::byte{};

			std::string frame{};

			if (ESC == bb)
			{
				bb = co_await std::byte{};
				if (SOF != bb)
				{
					continue; // not a start sequence 
				}

				while (true)  // try to capture the full frame
				{
					bb = co_await std::byte{};
					if (ESC == bb)
					{
						// skip this byte look at the next one!
						bb = co_await std::byte{};
						if (SOF == bb)
						{
							// if end of frame then return the result
							co_yield frame;
							break;
						}
						else if (ESC != bb)
						{
							// out of sync !!!
							break;
						}
					}

					frame += static_cast<char>(bb);
				}
			}
		}
	}







} // end of namespace AsyncParse

#endif // INCOMPLETE MACRO ; temporary