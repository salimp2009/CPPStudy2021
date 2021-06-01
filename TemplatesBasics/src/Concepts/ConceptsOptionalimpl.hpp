#pragma once
#include "Templpch.h"

/*TODO: this is InComplete*/
template<typename T>
union storage_t
{
	using aligned_storage_t = std::aligned_storage_t<sizeof(T), alignof(T)>;
	aligned_storage_t data;
	
	storage_t() = default;
	T* as() { return reinterpret_cast<T*>(&data); }
	// use placement new to create an instance of T inside this union ??
};

struct  copyable {};

struct notCopyable
{
	//notCopyable() = default;
	notCopyable(const notCopyable&) = delete;
	notCopyable& operator=(const notCopyable) = delete;
};


template<typename T>
class optional
{
public:
	optional() = default;

	optional(const optional& other) requires std::is_copy_constructible_v<T> = default;

	//template<typename U, typename =std::enable_if_t<std::is_same_v<U, optional> && std::is_copy_constructible_v<T>>>
	//optional(const U&) {};

	/* the ordering of concepts is from strong to weak constraint*/
	~optional() requires (not std::is_trivially_destructible_v<T>) 
	{  
		if (has_value)
		{
			value.as()->~T();
		}
	}

	~optional() = default;

private:
	storage_t<T> value;
	bool has_value{ true };
};

optional<notCopyable>a{};
//optional<notCopyable>b = a;

static_assert(not std::is_copy_constructible_v<optional<NotCopyable>>);
static_assert(std::is_copy_constructible_v<optional<int>>);

