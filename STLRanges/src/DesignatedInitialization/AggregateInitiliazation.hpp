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

inline auto Use()
{
	// Since RVOfunc returns a nonmovable or copyable type normally it should fails
	// but compiler creates this not on the stack ; right at the call stack so it does not move or copy it and compiles
	auto myVal = RVOfunc();
	fmt::print("Use creates NonCopyableorMovable x: {}\n", myVal.x);
	return RVOfunc();
}

inline auto GetVectorPoint3d()
{
	std::vector<Point3D> vec3d;

	vec3d.emplace_back(Point3D{ .x = 10, .y = 20, .z = 30 });
	vec3d.emplace_back(Point3D{ .y = 20, .z = 30 });
	vec3d.emplace_back(15, 25, 35);

	return vec3d;
}


struct FileAccessParameters
{
	bool open;
	bool close;
	bool readonly;
};

inline void FileAccess(const FileAccessParameters& params)
{
	fmt::print("open: {}, close: {}, readonly: {}\n", params.open, params.close, params.readonly);
}

struct  Point
{
	int X;
	int y;
};

inline void AddToPoint(Point2D point, int value)
{

	fmt::print("Add Point2D: result: x: {}, y:{}\n", point.x + value, point.y + value);
}

inline void AddToPoint(Point point, int value)
{
	fmt::print("Add Point; result: x: {}, y:{}\n", point.X + value, point.y + value);
}