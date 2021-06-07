#pragma once
#include "ConcurrencyPCH.h"

// TODO: InComplete!!!

#define INCOMPLETE 0

#if INCOMPLETE
namespace AsyncParse
{

	template<typename T, typename G, typename... Bases>
	struct promise_type_base: public Bases...
	{
	
	
	
	};

	template<typename T>
	struct awaitable_promise_type_base
	{

	};


	template<typename T, typename U>
	struct [[nodiscard]] async_generator
	{
		using promise_type = promise_type_base<T, async_generator, awaitable_promise_type_base<U> >;
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