#pragma once

inline void StopToken_Example()
{
	std::printf("\n---------------Stop Token Basics---------------------\n");

	using namespace std::literals;
	auto func = [](std::stop_token stoken) 
	{
		std::atomic<int>counter{ 0 };

		auto threadID = std::this_thread::get_id();
		std::stop_callback callBack(stoken, [&counter, &threadID]()
		{
				fmt::print("thread id: {0}, counter: {1}\n", threadID, counter);

		});

		while (counter < 10)
		{
			std::this_thread::sleep_for(0.2s);
			++counter;
		}
	};

	std::vector<std::jthread> vecThreads(10);

	for (auto& thr : vecThreads)
	{
		thr = std::jthread(func);
	}

	std::this_thread::sleep_for(1s);

	for (auto& thr : vecThreads)
	{
		thr.request_stop();
	}
}