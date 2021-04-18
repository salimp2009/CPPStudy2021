#pragma once

template<typename T, typename Cont = std::vector<T>>
class SPStack
{
private:
	Cont cont;
public:
	SPStack() = default;

	template<typename... U, typename =std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
	SPStack(U&&... args) noexcept(noexcept(Cont()) && noexcept(U())) : cont{std::forward<U>(args)...} { }
	
	constexpr void push(T&& elem) noexcept(noexcept(Cont));
	
	template<typename... U, typename=std::enable_if_t<(std::is_convertible_v<U,T> && ...)>>
	constexpr decltype(auto) emplace(U&&... elems) noexcept(noexcept(Cont)) { return (cont.emplace_back(std::forward<T>(elems)), ...); }

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
constexpr void SPStack<T, Cont>::push(T&& elem) noexcept(noexcept(Cont))
{
	cont.push_back(std::forward<T>(elem));
}