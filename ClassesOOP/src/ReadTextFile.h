#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"


inline void ReadFromFile()
{
	constexpr auto filename = "src/test.txt";
	std::ifstream inFile;
	inFile.open(filename);

	if (!inFile)
	{
		std::cerr << "File Not Found!!\n";
		return;
	}

	//std::cout <<"Filename: "<< filename <<", Is File Open: "<<inFile.is_open()<< '\n';
	fmt::print("Filename: {0}, is File Open: {1}\n ", filename, inFile.is_open());

	std::string line;


	while (!inFile.eof())
	{
		inFile >> line;
		fmt::print("File content: {}\n", line);
	}

	
	inFile.close();
}
