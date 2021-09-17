module;

#include <numeric>

module math;
/* the example shows numeric to be here but then it does compile with a warning because this is the field export / import 
	and standart library is not modularized ; might be a false warning !!!!
*/
//#include <numeric>

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



