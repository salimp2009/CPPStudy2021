#pragma once

struct Mytype
{
	Mytype(int, bool) {}
};

template <typename T, typename... Args>
[[nodiscard]] T* create(Args&&... args)
{
	return new T(std::forward<Args>(args)...);
}

enum class [[nodiscard]] ErrorCode
{
	Okay,
	Warning,
	Critical,
	Fatal
};

ErrorCode errorProneFunction() { return ErrorCode::Fatal; }