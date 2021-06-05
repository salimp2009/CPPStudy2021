#pragma once
#include "ConcurrencyPCH.h"

static  const std::byte ESC{ 'H' };
static const std::byte SOF{ 0x10 };

template<typename T>
void ProcessNextByte(std::byte, T&& frameCompleted)
{
	static std::string frame{};
	static bool inHeasder{ false };
	static bool wasESC{ false };
	static bool lookingForESC{ false };

}