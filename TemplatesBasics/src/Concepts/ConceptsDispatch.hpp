#pragma once
#include "Templpch.h"

/* Example Usage of Concepts*/

/* e.g; data packet/buffer for small size data packs over TCP/IP*/
/* ack = acknowledgement; limit 10 ack packs (requirements for the example);
	will be queued to 10 packets 
*/
std::array<char, 16> ackData;

/* e.g; data packet/buffer for bigger data packs over TCP/IP
	will be send immediately
*/

std::array<char, 100> payLoadData;

template<typename T>
concept ByteLikeType = std::is_same_v<char, T> || std::is_same_v<unsigned char, T>
|| std::is_same_v<const char, T> || std::is_same_v<const unsigned char, T>;




/* NOT Complete*/
void Send(/*SmallBuffer*/);
void Send(/*LargeBuffer*/);