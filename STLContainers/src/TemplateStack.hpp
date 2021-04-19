#pragma once

template<typename T, typename Cont = std::vector<T>>
class SPStack
{
private:
	Cont cont;
public:
	SPStack() = default;

	/* just implemented for learning purposes otherwise the below constructor with variadic is enough*/
	SPStack(std::initializer_list<T> ls) :cont{ ls } {}

	template<typename... U, typename =std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
	SPStack(U&&... args) noexcept(noexcept(Cont()) && noexcept(U())) : cont{std::forward<U>(args)...} { }
	
	template<typename... U, typename=std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
	constexpr decltype(auto) emplace(U&&... elems) noexcept(noexcept(Cont())) 
	{ 
		return (cont.emplace_back(std::forward<U>(elems)), ...); 
	}

	constexpr decltype(auto) emplace(T&& elems) noexcept(noexcept(Cont()))
	{
		return cont.emplace_back(std::forward<T>(elems));
	}

	constexpr void push(T&& elem) noexcept(noexcept(Cont()));

	const T& top()  const&;

	T pop();

	Cont::iterator begin() { return cont.begin(); }
	Cont::iterator end() { return cont.end(); }
	Cont::reverse_iterator rbegin() { return cont.rbegin(); }
	Cont::reverse_iterator rend() { return cont.rend(); }

	Cont::const_iterator cbegin() const { return cont.begin(); }
	Cont::const_iterator cend() const   { return cont.end(); }
	Cont::reverse_iterator rbegin()const { return cont.rbegin(); }
	Cont::reverse_iterator rend() const { return cont.rend(); }

};

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