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
		fmt::print("path does not exist {}!\n", p.string());
	}

}

inline void CheckPath_SwitchFile(/*int argc, char* argv[]*/)
{
	std::printf("\n-----CheckPath SwitchFile-----\n");
	/* if used from VS use this; if used with command line comment these 2 line and uncomment function inpuntsde*/
	int argc = 2;


	//const char* argv = "src/testfolder";
	//onst char* argv = "src/STLtest.cpp";
	const char* argv = ".";
		/* if no path / directory entered warn!!*; this is if used with command line !!*/
		if (argc < 2)
		{
			fmt::print("Please enter a path; Usage: {} <path> \n", argv[0]);
			return;
		}


		switch (std::filesystem::path p{ argv }; status(p).type())
		{
			case std::filesystem::file_type::not_found:
			{
				/* for windows not use see "\\" in the output use p.string()*/
				fmt::print("path does not exist!: {}\n", p);
				return;
			}

			case std::filesystem::file_type::regular:
			{
				fmt::print("{0} exists with {1} bytes\n", p, file_size(p));
				return;
			}

			case std::filesystem::file_type::directory:
			{
				fmt::print("{0} is a directory containing;\n", p);
				for (const auto& e : std::filesystem::directory_iterator{ p })
				{
					fmt::print("---- {0} \n", e.path().string());
				}
				return;
			}
		}
		fmt::print("path is a special file {}!\n", argv);
}
