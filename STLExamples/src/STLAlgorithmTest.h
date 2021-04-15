#pragma once

inline void STLAlgorithms_Test()
{
	std::printf("\n---------------STL Algorithms Test--------------------------\n");

	long sum{ 0 };
	std::vector coll1{ 1,2,3,4,5,7,8 };
	auto MeanVal = std::for_each(coll1.begin(), coll1.end(), [&sum](auto&& val)
		{
			sum += val;
		});

	double meanValue = static_cast<double>(sum) / static_cast<double>(coll1.size());

	fmt::print("mean value: {0:.3f}\n", meanValue);

	std::list<int> coll2 = { 1,2,3,4,5,6,7,8,9,10 };

	int count{ 0 };
	/* if remove_if used to remove the 3rd element only then use counter by ref otherwise it removes the second 3rd element*/
	/* better solution to use find the value and only erase that one if the container has one and such funct is needed or this*/
	/* for a list if you want to erase 3rd element use erase and give the pos*/
	auto pos=std::remove_if(coll2.begin(), coll2.end(), [&count](auto&& elem)
	{
		/*return true if it is 3rd element*/
		return ++count == 3;
	
	});

	coll2.erase(pos, coll2.end());

	printCont(coll2);

	/* add the first value of coll2 to each element; for each return predicate function by using std::move*/
	auto pred = std::for_each(std::next(coll2.begin()), coll2.end(), [=](auto&& elem) { elem += *coll2.begin(); });
	printCont(coll2);

	const auto coll3 = coll2;

	/* std::count and count_if return the total number that matches the values given or predicate (returns bool)*/
	auto numofCount = std::count_if(coll3.cbegin(), coll3.cend(), [](auto&& elem) noexcept {return elem > 4; });
		
	fmt::print("number of Counts : {}\n", numofCount);
	printCont(coll3);

	std::list<int>coll4(10);
	std::iota(coll4.begin(), coll4.end(), 0);
	printCont(coll4);
	coll4.push_back(4);
	
#if __has_include(<ranges>) && _HAS_CXX20
	/* search not only the first found but beyond*/
	/* ranges only used for testing purposes; not any benefit here 
		unless you combine with other algorithms using c++20 features
	*/
	std::list<int>::iterator pos1;
	std::list<int>::iterator pos2;
	const int value = 4;
	/* find and find_if normally stop at the first match value or condition to make it continue you need an "if" or a "loop" to continue*/
	if (pos1 = std::ranges::find(coll4, value); pos1 != coll4.end())
	{
		pos2 = std::ranges::find(++pos1, coll4.end(), value);

	}

	fmt::print("first pos1: {}\n", *(--pos1));
	
	/* print only between to find value */
	if (pos1 != coll4.end() && pos2 != coll4.end())
	{
		std::ranges::copy(pos1, ++pos2, std::ostream_iterator<int>(std::cout," "));
	}
#endif

}


inline void STLAlgorithms_Test2()
{
	std::printf("\n---------------STL Algorithms Test2--------------------------\n");

	std::deque<int> coll1 = {1,2,7,7,6,3,9,7,7,7,7,7,6,25,40 };
	printCont(coll1);
	const int value = 7;
	const int count = 3;
	/*search_n gives you the for given count of consecutive elements
	  returns pos of first one; e.g. search 3 consecutive of 7's;
	  the search stops at first match
	*/
	auto pos1=std::search_n(coll1.begin(), coll1.end(), count, value);
	if (pos1 != coll1.end())
	{
		auto dist = std::distance(coll1.begin(), pos1) + 1;
		fmt::print("the first three consecutive of sevens is at {}\n", dist);
	}

	/* if passed a predicate the predicate has two inputs ; first is the element in collection, second is a value 
		but the passed value does not neccessarily to be used; predicate needs to return a bool
		e.g; search for 3 consecutive odd elements; (stops at first match)
	*/
	auto pos2 = std::search_n(coll1.begin(), coll1.end(), count, 0,
		[](auto&& elem, auto&& value) { return elem % 2 == 1; });

	if (pos2 != coll1.end())
	{
		auto dist2 = std::distance(coll1.begin(), pos2) + 1;
		fmt::print("the first three consecutive of odd elems is at {}\n", dist2);
	}

	std::deque<int>coll2 = {4,5, 1,2,3,4,5,6,7,8, 4,5,6 };
	std::deque<int>subColl = { 4,5,6 };

	/*Search stop on the 1st match ; if not match return end() of container / range*/
	//auto pos3 = std::search(coll2.begin(), coll2.end(),		// the source container to search
	//						subColl.begin(), subColl.end());	// sub range to be searched for


	//if (pos3 != coll2.end())
	//{
	//	auto dist = std::distance(coll2.begin(), pos3) + 1;
	//	fmt::print("the subrange (4,5,6) found at pos: {}\n", dist);

	//}
	
	
	/* 1ST ALTERNATIVE to search all matching sub ranges to search for 
		for string there are different search methods that can be used 
		also std::string member find() member function is faster for strings
	*/
	for (auto pos3 = std::search(coll2.begin(), coll2.end(),			// the source container to search
		subColl.begin(), subColl.end()); pos3 != coll2.end();
		pos3 = std::search(pos3 + subColl.size(), coll2.end(), subColl.begin(), subColl.end()))
	{
		auto dist = std::distance(coll2.begin(), pos3) + 1;
		fmt::print("the subrange (4,5,6) found at pos: {}\n", dist);
	}

	/* 2ND ALTERNATIVE using boyer_moore_search algorithm; used for big text data searchs
		this is the fastest search for bigger search texts; NOTE: Uses to much memory!!!
	*/
	std::boyer_moore_searcher bmsearch{ subColl.begin(), subColl.end() };
	for (auto pos3 = std::search(coll2.begin(), coll2.end(),			
		bmsearch); pos3 != coll2.end(); pos3 = std::search(pos3 + subColl.size(), coll2.end(), bmsearch))
	{
		auto dist = std::distance(coll2.begin(), pos3) + 1;
		fmt::print("the subrange  BOYER_MOORE SEARCH (4,5,6) found at pos: {}\n", dist);
	}

	std::vector<int> vec1 = { 1,2,3,4,5,6,7,8,9 };
	bool checkEvenArgs[3] = { true, false, true };
	printCont(vec1);
	
	auto pos4 = std::search(vec1.begin(), vec1.end(), checkEvenArgs, checkEvenArgs + std::size(checkEvenArgs),
		[](auto&& elem, bool cond)
		{
			if (cond == true)
			{
				return elem % 2 == 0;
			}
			else
			{
				return elem % 2 == 1;
			}

		});

	if (pos4 != vec1.end())
	{

		fmt::print("even: {0}, odd: {1}, even{2}\n", *pos4, *(pos4+1), *(pos4+2));
	}

	auto searchPred = [](auto&& elem, bool cond) 
	{
		if (cond == true)
		{
			return elem % 2 == 0;
		}
		else
		{
			return elem % 2 == 1;
		}

	};

	for (auto pos5 = std::search(vec1.begin(), vec1.end(), checkEvenArgs, checkEvenArgs + std::size(checkEvenArgs), searchPred); 
		pos5!= vec1.end();
		pos5= std::search(++pos5, vec1.end(), checkEvenArgs, checkEvenArgs + std::size(checkEvenArgs), searchPred))
	{
		auto dist = std::distance(vec1.begin(), pos5) + 1;
		fmt::print("found match (even, odd, even) at pos: {}\n", dist);

	}
}
