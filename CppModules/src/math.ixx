module;

/* Global module starts with module then includes and the export module name*/

#include <numeric>
#include <vector>


export module math;

export int add(int first, int second)
{
	return first + second;
}

export int getProductNew(const std::vector<int>& vec)
{
	return std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
}