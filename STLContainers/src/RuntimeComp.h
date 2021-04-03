#pragma once

class RuntimeComp
{
public:
	enum cmp_mode {normal, reverse};

private:
	cmp_mode mode;

public:
	RuntimeComp(cmp_mode m = normal) :mode{ m } { }

	/*compare any two elements*/
	template<typename T, typename = std::enable_if_t<!std::is_same_v<T, RuntimeComp>> >
	bool constexpr operator()(T&& t1, T&& t2) const
	{
		return mode == normal ? t1 < t2 : t2 < t1;
	}

	/*check for sort criteria; reverse or normal*/
	bool constexpr operator==(const RuntimeComp& rc) const
	{
		return mode == rc.mode;
	}
};