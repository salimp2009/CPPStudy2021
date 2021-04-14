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



}
