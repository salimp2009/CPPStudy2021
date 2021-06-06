#pragma once
#include "CoroutinesLazyGenerator.hpp"
#include "CoroutineFactoryBasics.hpp"
#include "CoroutinesEagerFuture.hpp"
#include "ByteStreamParserOLDWay.hpp"

inline void LazyGenerator_Coroutine()
{
	std::printf("\n--LazyGenerator_Coroutine--\n");
	UseCounter();
}

/* not complete DONT Call it*/
#define COMPILE_USE 0

#if  COMPILE_USE
inline void CoroutineFactory_Basics()
{
	/* function declaration that returns a coroutine object*/
	Generator<int> coroutineFactory();
	
	auto gen = coroutineFactory();
	gen.next();
	auto result = gen.getvalue();
}
#endif //  COMPILE_USE

EagerFuture<int> createFuture(int val)
{
	co_return val++;
}

inline void EagerFuture_Coroutine()
{
	std::printf("\n--EagerFuture_Coroutine--\n");

	auto fut = createFuture(2020);

	fmt::print("eager future result : {}\n", fut.get());

}

inline void ByteStreamParser_OLDWAY()
{
	std::printf("\n--ByteStreamParser_OLDWAY--\n");


}






