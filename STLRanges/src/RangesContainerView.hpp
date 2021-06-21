#pragma once
#include "RangesPCH.hpp"

template<std::ranges::input_range Range>
requires std::ranges::view<Range>
class ContainerView :public std::ranges::view_interface<ContainerView<Range>>
{
private:

public:
	ContainerView() = default;




};