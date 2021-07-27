#pragma once

// typical aggregate initilazation; 
// no user defined constructor or inherited 
// no virtual members functions
// no private or protected non-static data members
// no private virtual, private or protected base classes; only public base classes

struct Point2D
{
	int x;
	int y;
};

class Point3D
{
public:
	int x;
	int y;
	int z;
};

struct NamedPoint
{
	std::string name;
	Point3D pt;
};

struct NonCopyableorMovable
{
	NonCopyableorMovable() = default;
	NonCopyableorMovable(const NonCopyableorMovable&) = delete;
	NonCopyableorMovable(NonCopyableorMovable&&) = delete;

	NonCopyableorMovable& operator==(const NonCopyableorMovable&) = delete;
	NonCopyableorMovable& operator==(NonCopyableorMovable&&) = delete;
	~NonCopyableorMovable() = default;

	int x = 2;
};

// testing Return Value Optimization for NonCopyorMovable class
NonCopyableorMovable RVOfunc()
{
	return {};
}

auto Use()
{
	// Since RVOfunc returns a nonmovable or copyable type normally it should fails
	// but compiler creates this not on the stack ; right at the call stack so it does not move or copy it and compiles
	auto myVal = RVOfunc();
	fmt::print("Use creates NonCopyableorMovable x: {}\n", myVal.x);
	return RVOfunc();
}
