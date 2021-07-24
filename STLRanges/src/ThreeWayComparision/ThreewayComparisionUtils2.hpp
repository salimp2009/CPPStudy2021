#pragma once
#include "RangesPCH.hpp"

struct Address
{

	std::string city;
	std::string street;
	std::int32_t streetNo;

	constexpr auto operator<=>(const Address& rhs) const
	{
		if (const auto& cmp = city <=> rhs.city; cmp != 0)
		{
			return cmp;
		}
		else if (const auto& streetcmp = street <=> rhs.street; streetcmp != 0)
		{
			return streetcmp;
		}

		// sort street_no ascending
		return rhs.streetNo <=> streetNo;
	}

	bool operator==(const Address&) const = default;
};

struct Legacy
{
	int a;

	// pre c++20 these define weak_order
	bool operator==(const Legacy&) const { return true; }
	bool operator<(const Legacy&) const { return true; }
};


