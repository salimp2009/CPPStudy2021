#pragma once


template<typename T>
class MyAlloc
{
public:
	typedef T value_type;

	//constructor
	MyAlloc() noexcept {}

	template<typename U>
	MyAlloc(const MyAlloc<U>&) noexcept {}

	/*allocate but dont initialize!*/
	T* allocate(std::size_t num)
	{
		return static_cast<T*>(::operator new(num * sizeof(T)));
	}

	void deallocate(T* p, std::size_t num)
	{
		::operator delete(p);
	}

};