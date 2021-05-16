#pragma once
#include "STLpch.h"

#include <filesystem>

inline void FileSystem_Basics(/*int argc, char* argv[]*/)
{
	std::printf("\n-------------FileSystem C++17-------------\n");
	/* if used from VS use this; if used with command line comment these 2 line and uncomment function inpuntsde*/
	int argc = 2;

	//const char* argv = "src/testfolder";
	//const char* argv = "src/STLtest.cpp";
	const char* argv = ".";
	/* if no path / directory entered warn!!*; this is if used with command line !!*/
	if (argc < 2)
	{
		fmt::print("Please enter a path; Usage: {} <path> \n", argv[0]);
		return;
	}

	std::filesystem::path p{argv}; // p is the file path given
	if (is_regular_file(p))
	{
		fmt::print("{0} exists with {1} bytes\n",p, file_size(p));
	}

	else if (is_directory(p))
	{
		fmt::print("{0} is a directory containing;\n", p);
		for (const auto& e : std::filesystem::directory_iterator{ p })
		{
			/* e.path() is normally neccessary but if used for output Windows put extra slashes
				then .string() will work but more expensive!
			*/
			fmt::print("----{} \n", e.path().string());
		
		}
	}
	else if (exists(p))
	{
		fmt::print("{0} is a special file\n", p.string());
	}
	else
	{
		fmt::print("path does not exist!\n", p.string());
	}

}


