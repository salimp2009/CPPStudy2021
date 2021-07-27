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
