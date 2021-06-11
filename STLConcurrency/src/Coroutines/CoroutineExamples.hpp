#pragma once
#include "CoroutinesLazyGenerator.hpp"
#include "CoroutineFactoryBasics.hpp"
#include "CoroutinesEagerFuture.hpp"
#include "ByteStreamParserOLDWay.hpp"
#include "CortnInfiniteDataStream.hpp"


inline void LazyGenerator_Coroutine()
{
	std::printf("\n--LazyGenerator_Coroutine--\n");
	UseCounter();
}


EagerFuture<int> createFuture(int val)
{
	co_return val;
}

inline void EagerFuture_Coroutine()
{
	std::printf("\n--EagerFuture_Coroutine--\n");

	auto fut = createFuture(2020);

	fmt::print("eager future result : {}\n", fut.get());
	fmt::print("eager future result : {}\n", fut.get());
}

inline void ByteStreamParser_OLDWAY()
{
	std::printf("\n--ByteStreamParser_OLDWAY--\n");
	const std::vector<std::byte> fakeBytes1{
		std::byte{0x70}, std::byte{0x24}, ESC, SOF, ESC,
		std::byte{'H'}, std::byte{'e'}, std::byte{'l'}, std::byte{'l'}, std::byte{'o'}, 
		ESC, SOF, std::byte{0x7}, ESC, SOF };

	auto frameCompleteHandler = [](std::string_view res) {  fmt::print("CCCB: {}", res); };
	for (const auto& data : fakeBytes1)
	{
		ProcessNextByte(data, frameCompleteHandler);
	}
	const std::vector<std::byte> fakeBytes2{ std::byte{'W'}, std::byte{'o'}, std::byte{'r'}, std::byte{'l'}, std::byte{'d'}, ESC, SOF, std::byte{0x99} };
	for (const auto& data : fakeBytes2)
	{
		ProcessNextByte(data, frameCompleteHandler);
	}
}

inline void InfinitiDataStream_Cornt()
{
	std::printf("\n--InfinitiDataStream_Cornt--\n");
	auto datagen = getNextData();
	std::printf("\ngetNext(0, 1): ");
	for (int i =0; i<=10; ++i)
	{
		datagen.next();
		std::printf("%d ", datagen.getValue());
	}

	std::printf("\ngetNext(100, -10): ");
	auto datagen2 = getNextData(100, -10);
	for (int i = 0; i <= 10; ++i)
	{
		datagen2.next();
		std::printf("%d ", datagen2.getValue());
	}
}

