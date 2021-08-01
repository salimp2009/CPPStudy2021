#pragma once
#include "RangesPCH.hpp"
#include "NonTypeTemplateParams.hpp"


inline void floatingPointNTTP()
{
	std::printf("\n-floatingPointNTTP-\n");

	// floating points are not equal 0.6-0.2 != 0.4 and uses different bit pattern when there is negative sign involved
	static_assert(! std::is_same_v<ADouble<+0.6 - 0.2>, ADouble<0.4>>);

	// +0.0 and -0.0 uses different bit pattern -1 is used to express negative sign at most left byte
	static_assert(!std::is_same_v<ADouble<+0.0>, ADouble<-0.0>>);

	// +0.0 == -0.0 is accepted equal in fp standarts
	static_assert(+0.0 == -0.0);

	// 0.1+0.1 == 0.2 and also uses same bit battern since no negative (but for number with more digits this might change due to machine Epsilon!!
	static_assert(std::is_same_v<ADouble<0.1 + 0.1>, ADouble<0.2>>);

	static_assert(+0.1+0.1 == 0.2);


}

