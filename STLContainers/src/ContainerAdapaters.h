#pragma once
#include "TemplateStack.hpp"

inline void StackExamples()
{
	std::printf("\n---------------------Stack Test- LIFO(Last in First Out)------------------------------------\n\n");

	std::stack<int> st1;

	st1.push(1);
	st1.push(2);
	st1.push(3);

	fmt::print("top: {}\n", st1.top());
	st1.pop();
	fmt::print("top: {}\n", st1.top());
	st1.top() = 255;
	fmt::print("top: {}\n", st1.top());

	int val{ 0 };
	if (!st1.empty())
	{
		val = st1.top();
		st1.pop();
	}
	fmt::print("top: {}\n", st1.top());
	fmt::print("val (old st1 top): {}\n", val);

	SPStack<int>mstack{ 1,2,3,4,5,70,8,9,10 };

	//mstack.push(1);
	fmt::print("mstack top: {}\n", mstack.top());

	auto stackval = mstack.emplace(6, 7, 8);
	fmt::print("mstack top: {}\n", mstack.top());
	fmt::print("mstack top: {}\n", stackval);

	SPStack<int>mstack2{ mstack };
	mstack2.emplace(55);
	fmt::print("mstack top: {}\n", mstack2.top());

	SPStack<std::string>mstack3{ "Salim", "Didem", "Demir" };
	fmt::print("mstack top: {}\n", mstack3.top());

	auto removedval = mstack3.pop();
	fmt::print("mstack top: {}\n", mstack3.top());
	fmt::print("mstack top: {}\n", removedval);
	mstack3.push("Semos");
	fmt::print("mstack top: {}\n", mstack3.top());

	for (auto elem : mstack3)
	{
		fmt::print("{0}{1} ", elem, (elem==mstack3.top() ? " ":", "));
	}

	SPStack<float*> mstack4;
	mstack4.emplace(new float(5));
	fmt::print("mstack top: {}\n", *mstack4.top());
	auto fptr = mstack4.pop();
	fmt::print("mstack top: {}\n", *fptr);
	delete fptr;

	SPStack<SPStack<int>>mstack5{ 1,2,3 };

	fmt::print("mstack top: {}\n", mstack5.top().top());
	

	SPStack<std::pair<int, float>>mstack6;
	mstack6.push({ 4,45.0f });
	fmt::print("mstack top: {}\n", mstack6.top().second);
	mstack6.emplace(std::make_pair(12, 12.5f ), std::make_pair( 12, 35.5F ));
	mstack6.emplace({ 12, 34.4f });

	std::vector<std::pair<int, float>> vec1{ { 4,45.0f } };
	vec1.emplace_back(12, 12.5f);

}

inline void Queues_Examples()
{
	std::printf("\n---------------------Queues Test- FIFO(First-in-First-Out)------------------------------------\n\n");

	std::queue<std::string>q1;
	q1.push("Salim");
	fmt::print("queue front: {}\n", q1.front());
	q1.push("Didem");
	q1.push("Demir");
	q1.push("Semos");
	fmt::print("queue front: {}\n", q1.front());
	fmt::print("queue front: {}\n", q1.back());
	q1.pop();
	fmt::print("queue front: {}\n", q1.front());
}