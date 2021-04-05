#pragma once

#include "STLContpch.h"
#include "ContainerUtilities.hpp"

inline void UnorderedCont_Test()
{
	fmt::print("\n---------------------Unordered Containers Test------------------------------------\n\n");

	std::unordered_map<std::string, float>mcoll1 = { {"Salim", 51.0f}, {"Didem", 50.0f}, {"Semos", 68.0f}, {"Demir", 16.0f} };
	mcoll1.max_load_factor(0.7f);
	fmt::print("load factor: {0}, bucket count: {1} \n", mcoll1.load_factor(), mcoll1.bucket_count());
	
	printMCont(mcoll1);

	static_assert(std::is_same_v<typename std::unordered_map<std::string, float>::value_type, std::pair<const std::string, float>>);

	/** Iterate over each bucket; buckets has their local iterator that goes thru
		Therefore you have first getinto bucket star from zero to bucket_count
		Once you are in a bucket you go over each elemet using iterator
	*/
	for (std::size_t idx = 0; idx != mcoll1.bucket_count(); ++idx)
	{
		std::cout << " b[" << std::setw(2) << idx << "]: ";
		for (auto pos = mcoll1.begin(idx); pos != mcoll1.end(idx); ++pos)
		{
			std::cout <<*pos<<" ";
		}
		std::cout << '\n';
	}

	mcoll1["Salim"] = 52;
	printMCont(mcoll1);

	auto newpos=mcoll1.find("Didem");
	if (newpos != mcoll1.end()) newpos->second = 51;
	printMCont(mcoll1);


}