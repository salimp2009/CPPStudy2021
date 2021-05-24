#pragma once

template<typename T, class Cont = std::vector<T>>
class SPStack
{
private:
	Cont cont;
public:
	SPStack() = default;

	SPStack(T elem) : cont({std::move(elem) }) {}

	/* just implemented for learning purposes otherwise the below constructor with variadic is enough*/
	//SPStack(std::initializer_list<T> ls) :cont{ ls } {}

	template<typename... U, typename =std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
	SPStack(U&&... args) noexcept(noexcept(Cont())) : cont{std::forward<U>(args)...} { }
	
	template<typename... U, typename=std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
	constexpr decltype(auto) emplace(U&&... elems) noexcept(noexcept(Cont())) 
	{ 
		return (cont.emplace_back(std::forward<decltype(elems)>(elems)), ...); 
	}

	constexpr decltype(auto) emplace(T&& elems) noexcept(noexcept(Cont()))
	{
		return cont.emplace_back(std::forward<T>(elems));
	}

	constexpr void push(T&& elem) noexcept(noexcept(Cont()));

	const T& top()  const&;
	T pop();
	bool empty() const { return cont.empty(); }

	template<typename T2>
	SPStack& operator=(const SPStack<T2>& other);

	/* needed to acces private of a stack with different type of elements in the container*/
	template<typename> friend class Stack;

	Cont::iterator begin() { return cont.begin(); }
	Cont::iterator end() { return cont.end(); }
	Cont::reverse_iterator rbegin() { return cont.rbegin(); }
	Cont::reverse_iterator rend() { return cont.rend(); }

	Cont::const_iterator cbegin() const { return cont.begin(); }
	Cont::const_iterator cend() const   { return cont.end(); }
	Cont::reverse_iterator rbegin()const { return cont.rbegin(); }
	Cont::reverse_iterator rend() const { return cont.rend(); }

};

SPStack(const char*)->SPStack<std::string>;


template<typename T, typename Cont>
const T& SPStack<T,Cont>::top() const&
{
	assert(!cont.empty());
	return cont.back();
}


template<typename T, typename Cont>
T SPStack<T, Cont>::pop()
{
	assert(!cont.empty());
	T temp = cont.back();
	cont.pop_back();
	return temp;
}


template<typename T, typename Cont>
constexpr void SPStack<T, Cont>::push(T&& elem) noexcept(noexcept(Cont()))
{
	cont.push_back(std::forward<T>(elem));
}

template<typename T, typename Cont >
template<typename T2>
SPStack<T, Cont>& SPStack<T, Cont>::operator=(const SPStack<T2>& other)
{
	if (*this == &other) return *this;
	static_assert(std::is_convertible_v<T2, T>);
	
	if (!other.empty())
	{
		cont.clear();
		cont.insert(cont.begin(), other.cont.begin(), other.cont.end());
	}
	
	return *this;
}