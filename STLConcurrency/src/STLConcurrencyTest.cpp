#include "ConcurrencyPCH.h"
#include "FuturesBasics.h"


int main()
{

	std::printf("hello from main\n");
	std::vector vec1{ 1,2,3,4,5,6 };
	printCont(vec1);

	FutureBasics_Test();
}