#include "STLContpch.h"
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"


void Array_Test()
{
	std::printf("\n---------------------Type Traits------------------------------------\n\n");

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
}



int main()
{
	Array_Test();




}