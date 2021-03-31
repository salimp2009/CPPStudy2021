#include "STLContpch.h"
#include "ContainerUtilities.hpp"



void Array_Test()
{
	std::printf("\n---------------------Array Test------------------------------------\n\n");

	std::array<int, 5> arr1 = { 45 };
	std::cout << arr1[0] << ", " << arr1[1] << '\n';

	std::array<int, 5>arr2({ 10,5,67,88 });
	std::cout << arr2[0] << ", " << arr2[4] << '\n';

	/* both type and the number of elements needs to match; */
	std::swap(arr1, arr2);
	std::cout << arr1[0] << ", " << arr1[1] << '\n';

	std::cout<<std::boolalpha<< (&arr2[1] == &arr2[0] + 1)<<'\n';

	[[maybe_unused]] bool result = arr2.data()[1]== arr2.data()[0]+1;
	std::cout << arr2.data() <<", "<< &arr2.data()[0]<<", "<< &arr2[0] + 1<< '\n';
	std::printf("%i \n", arr2[0]);

	std::cout <<"size of array: "<<arr2.size() << '\n';

	std::swap(arr1, arr2);
	auto sum = std::accumulate(arr2.begin(), arr2.end(), 0, [](auto&& val, auto&& x) { return std::move(val) + x; });
	std::cout << "sum with lambda: " << sum << '\n';	
	
	sum = std::accumulate(arr2.begin(), arr2.end(), 0);
	std::cout << "sum: " << sum << '\n';

	fmt::print("fmt prints: {0}\n", sum);

	std::transform(arr2.begin(), arr2.end(), 
				   arr2.begin(),
				   [](auto& elem) { return -elem; });

	fmt::print("negated array: ({0}), ({1}) \n", arr2[0], arr2[1]);

	std::printf("\n---------------------Array Test------------------------------------\n\n");
}

void Vector_Test()
{
	std::printf("\n---------------------VectorTest------------------------------------\n\n");
	std::vector<int>v;
	/* allocate memory for 20 elements of type int; note it invalidates any existing pointers */
	v.reserve(20);

	fmt::print("v capacity: {0}\n", v.capacity());
	v = { 5,25,13,1,1 };
	for (const auto& elem : v)
	{
		fmt::print("elem: {0} ", elem);
	}
	
	/* Invalidate pointers*/
	//v.shrink_to_fit();
	//fmt::print("new v capacity: {0}\n", v.capacity());

	if (v.size() > 1)
	{
		if constexpr (std::is_same_v< std::vector<int>::iterator::iterator_category::bidirectional_iterator_tag, std::bidirectional_iterator_tag>)
		{
			/* this might fail if the vector iterator is implemented as ordinary pointer*/
			/* because ++ operator is not valid for temp values but ok for classes..*/
			std::sort(++v.begin(), v.end());
		}
		else
		{
			/*this wont fail even if the vector iterator is regular pointer*/
			std::sort(std::next(v.begin()), v.end());
		}

	}
	std::cout<< '\n';
	for (const auto& elem : v)
	{
		fmt::print("elem: {0} ", elem);
	}

	/** remove looks for a value from begin to end and removes all the match elements to the end
		and returns the pos of the first removed element but elements are still in the contaier;
		then erase deletes from the given pos to the end so all matching elements are removed
	*/
	v.erase(std::remove(v.begin(), v.end(), 1), v.end());
	
	/*std::cout << '\n';
	for (const auto& elem : v)
	{
		fmt::print("elem: {0} ", elem);
	}*/

	std::cout <<"vector overloaded: "<< v << '\n';

	std::vector<std::string>sentence;
	sentence.reserve(5);
	sentence.emplace_back("Hello");
	sentence.insert(sentence.end(), { "Didem","Demir","Semos" });

	std::cout <<"family:"<< sentence << '\n';
	/* insert before the position passed; e.g.; before "Demir"*/
	sentence.emplace(std::find(sentence.begin(), sentence.end(), "Demir"), "Salim");
	std::cout << "family added:" << sentence << '\n';

	std::exchange(sentence[0], "Semsetting");

	fmt::print("{}", sentence[0]);

	std::printf("\n---------------------VectorTest------------------------------------\n\n");
}

void Deque_Test()
{
	fmt::print("\n---------------------Deque Test------------------------------------\n\n");

	std::deque<int> deq1 = { 1,5,3,15 };
	deq1.push_front(35);

	std::cout << deq1.front() << '\n';
}


int main()
{
	//Array_Test();
	//Vector_Test();
	Deque_Test();


}