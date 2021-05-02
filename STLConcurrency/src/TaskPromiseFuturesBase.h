#pragma once

#include "ConcurrencyUtility.hpp"


inline void FireForgetFutures()
{
	std::printf("\n------FireForgetFutures------\n");
/* if run this way it runs as a sequential since the std::async holds on it destructpr and block
	and also you will get a return value is no discard 
*/
  auto fut1 = std::async(std::launch::async, []()
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			fmt::print("first thread!!\n");
		});


 auto fut2 = std::async(std::launch::async, []()
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			fmt::print("second thread!!\n");
		});


	fmt::print("main thread!!\n");
}


inline void dotProductAsync()
{
	std::printf("\n------ dot Product with Async------\n");

	static const int NUM = 100'000;

	auto dotProduct = [](const std::vector<int>& v, const std::vector<int>& w) noexcept
	{
		auto vSize = v.size();

		auto future1 = std::async([&] {
			//return std::inner_product(&v[0], &v[vSize / 4], &w[0], 0LL);
			return std::inner_product(v.begin(), v.begin() + vSize / 4, w.begin(), 0LL);
			});

		auto future2 = std::async([&] {
			//return std::inner_product(&v[vSize / 4], &v[vSize / 2], &w[vSize / 4], 0LL);
			return std::inner_product(v.begin() + vSize / 4, v.begin() + vSize / 2, w.begin() + vSize / 4, 0LL);
			});

		auto future3 = std::async([&] {
			//return std::inner_product(&v[vSize / 2], &v[vSize * 3 / 4], &w[vSize / 2], 0LL);

			return std::inner_product(v.begin() + vSize / 2, v.begin() + vSize * 3 / 4, w.begin() + vSize / 2, 0LL);
			});

		auto future4 = std::async([&] {
			//return std::inner_product(&v[vSize * 3 / 4], &v[vSize], &w[vSize * 3 / 4], 0LL);

			return std::inner_product(v.begin() + vSize * 3 / 4, v.end(), w.begin() + vSize * 3 / 4, 0LL);

			});

		return future1.get() + future2.get() + future3.get() + future4.get();

	};

	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution<int> dist(0, 100);

	std::vector<int> v, w;
	v.reserve(NUM);
	v.reserve(NUM);

	for (auto i = 0; i < NUM; ++i)
	{
		v.push_back(dist(engine));
		w.push_back(dist(engine));
	}
	std::cout<<"dot product : "<<dotProduct(v, w)<<'\n';

	//std::vector<int> vec1 = { 1,2,3,4 };
	//std::vector<int> vec2 = { 1,2,3,4 };

	//auto result = std::inner_product(&vec1[0], &vec1[vec1.size()], &vec2[0], 0);

	//std::cout << result << '\n';

}

