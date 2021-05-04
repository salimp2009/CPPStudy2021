#pragma once

inline void SortParallel_Basics()
{
	std::printf("\n-----SortParallel-----\n");

	std::vector<int> vec1 = { 1,2,3,4,5,6,7,8,9 };

	std::sort(vec1.begin(), vec1.end());

	std::sort(std::execution::par, vec1.begin(), vec1.end());

	/* VS implentation of std::execution::par_unseq is same as std::execution::par*/
	std::sort(std::execution::par_unseq, vec1.begin(), vec1.end());
	printCont(vec1);

	
	std::cout << std::is_execution_policy_v<float> << '\n';

}

inline void ForEachParallel_Basics()
{
	std::printf("\n-----ForEachParallel-----\n");

	std::vector<int> vec1 = { 1,2,3,4,5,6,7,8,9 };
	std::atomic<int> sum{ 0 };
	

//	std::for_each(std::execution::par, vec1.begin(), vec1.end(), [&](auto&& elem) {sum += elem+elem; });
	std::for_each(std::execution::par_unseq, vec1.begin(), vec1.end(), [&](auto&& elem) 
		{
			sum += elem + elem; 
			std::cout<<std::this_thread::get_id()<<'\n';
		
		});

	printCont(vec1);

	fmt::print("sum: {}\n", sum);



}



