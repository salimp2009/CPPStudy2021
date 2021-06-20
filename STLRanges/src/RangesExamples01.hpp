#pragma once
#include "RangesPCH.hpp"


inline void RangeExample01()
{
	std::printf("\n---RangeExample01---\n");

	const std::vector<int> numbers = { 1,2,3,4,5,6};

	auto result = numbers | std::views::filter([](int n) { return n % 2 == 0; })
						  | std::views::transform([](int n) { return n * 2; });
						  //| std::ranges::views::split(2);

	for (auto v : result)
	{
		fmt::print("{} ", v);
		
	}
	puts("\n");

	std::vector<int> vec2 = { -3,5,0,7,-4 };
	std::ranges::sort(vec2);
	for (const auto elem : vec2)
	{
		fmt::print("{} ", elem);
	}
	puts("\n");
}


struct PhoneBookEntry
{
	std::string name;
	int number = 0;
};

void PrintPhonebook(std::span<PhoneBookEntry> phoneBook)
{
	for (auto elem : phoneBook)
	{
		fmt::print("name: {}, number: {}\n", elem.name, elem.number);
	}
		
}


inline void RangeProjection()
{
	std::printf("\n--- RangeProjection---\n");

	std::vector<PhoneBookEntry> phonebook = { {"Salim", 222}, {"Didem", 568}, {"Taylor", 145}, {"Frank", 558} };

	puts("\nranges with default sort: less(); projection; name to sort");
	std::ranges::sort(phonebook, {}, &PhoneBookEntry::name);
	PrintPhonebook(phonebook);

	puts("\nranges with default sort: less(); projection; number to sort");
	std::ranges::sort(phonebook, {}, &PhoneBookEntry::number);
	PrintPhonebook(phonebook);

	puts("\nranges with default ranges::greater(); projection; number to sort");
	std::ranges::sort(phonebook, std::ranges::greater(), &PhoneBookEntry::number);
	PrintPhonebook(phonebook);

}

inline void ViewsKeysValue_Test()
{
	std::printf("\n--- Views:KeysValue---\n");

	std::unordered_map<std::string, int>freqWord = { {"witch", 25}, {"wizard", 33}, {"tale", 45}, {"dog", 4}, {"cat", 34}, {"fish", 23}};
	puts("Keys:");
	auto names = std::views::keys(freqWord);

	for (const auto& name : names)
	{
		fmt::print("{} ", name);
	}
	puts("\nValues: ");

	for (auto value : std::views::values(freqWord))
	{
		fmt::print("{} ", value);
	}
}

inline void ViewsKeys_FunctCompose()
{
	std::printf("\n--- Views:KeysValue---\n");

	std::map<std::string,int>freqWord2 = { {"witch", 25}, {"wizard", 33}, {"tale", 45}, {"dog", 4}, {"cat", 34}, {"fish", 23} };
	puts("\nWords:");
	for (const auto& name : std::views::keys(freqWord2))
	{
		fmt::print("{} ", name);
	}
	puts("\n\nAll Words Reverse Order: ");
	for (const auto& name : std::views::keys(freqWord2) | std::views::reverse)
	{
		fmt::print("{} ", name);
	}
	puts("\n\nThe First 4 Words: ");

	//TODO: MSVC Bug does not compile; give a narrowing error !!!; propose solution is on github/VS Developer site; 
	// https://developercommunity.visualstudio.com/t/Compile-error-with-std::ranges::views::k/1397309?from=email&viewtype=all&space=62&q=ranges+
	// https://github.com/microsoft/STL/pull/1844
	//for (const auto& name : std::views::keys(freqWord2) | std::views::take(4))
	//{
	//	fmt::print("{} ", name);
	//}

	puts("\n\nName Starts with 'w': ");

	auto firstLetterW = [](const std::string& name) { return name[0] == 'w'; };

	for (const auto& name : std::views::keys(freqWord2) | std::views::filter(firstLetterW))
	{
		fmt::print("{} ", name);
	}

	puts("\nend ofName Starts with 'w': ");
	
}


