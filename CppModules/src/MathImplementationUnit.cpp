module;
#include <numeric>

module math;
/* the example shows numeric to be here but then it does not compile because this is the field export / import 
	and standart library is not modularized ; maybe in c++23
*/

namespace math
{
	 int add(int first, int second)
	{
		return first + second;
	}

	int getProduct(const std::vector<int>& vec)
	{
		return std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
	}

}



