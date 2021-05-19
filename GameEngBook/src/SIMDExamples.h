#pragma once

#include "GameEnginePCH.h"
#include <xmmintrin.h>


void AddArrays_sse(std::size_t count, float* results, const float* dataA, const float* dataB)
{

	/*size of all 3 arrays needs to match and a multiple of four*/
	assert(count % 4 == 0);

	for (auto i = 0; i < count; i += 4)
	{
		/* load the first 4 in each array and sums them up and loads the next 4 if any*/
		__m128 a = _mm_load_ps(&dataA[i]);
		__m128 b = _mm_load_ps(&dataB[i]);
		__m128 r = _mm_add_ps(a, b);
		/* every add of 4 values will be stored in array contigously ; 
			each element of the result array will result of added 4 values in given arrays
		*/
		_mm_store_ps(&results[i], r);
	}
}




inline void TestAddSSE()
{
	std::printf("\n---------------SIMExamples TestAddSSE------------------------\n");

	alignas(16) float A[4];
	alignas(16) float B[4] = { 2.0f, 4.0f, 6.0f, 8.0f };

	/* this is similar to seting a[] ={1,2,3,4}
		but SIMD _mm_set_ps() reads from reverse order
	*/
	__m128 a = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
	__m128 b = _mm_load_ps(&B[0]);

	/* add vectors*/
	__m128 r=  _mm_add_ps(a, b);

	/* store the _mm128 a in an array in the  empty array*/
	_mm_store_ps(&A[0], a);

	alignas(16) float R[4];
	_mm_store_ps(&R[0], r);

	fmt::print("array A: {0}\n", fmt::join(A, ", "));
	fmt::print("array B: {0}\n", fmt::join(B, ", "));
	fmt::print("A+B (SIMD ops): {0}\n", fmt::join(R, ", "));

	alignas(16) float results[std::size(A)];
	AddArrays_sse(std::size(A), results, A, B);
	fmt::print("array results: {0}\n", fmt::join(results, ", "));


	
}
