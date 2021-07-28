#pragma once
#include "RangesPCH.hpp"
#include "AggregateInitiliazation.hpp"

inline void AggregateIinitialization()
{
	std::printf("\n-AggregateIinitialization-\n");

	Point2D point2dOne{ .x = 20, .y = 45 };

	Point3D point3dOne{ 30, 55,15 };

	fmt::print(" point2dOne: x:{}, y: {}\n", point2dOne.x, point2dOne.y);
	fmt::print(" point3dOne: x:{}, y: {}, z:{}\n", point3dOne.x, point3dOne.y, point3dOne.z);

	NamedPoint namedpoint1{ .name{"start"}, .pt{0, 12, 15} };
	NamedPoint namedpoint2{ .name{"start"}, .pt{.x = 20, .y = 15, .z = 45 } };

	fmt::print(" namedpoint1; name: {0}, Point: [{1}, {2}, {3}]\n", namedpoint1.name, namedpoint1.pt.x, namedpoint1.pt.y, namedpoint1.pt.z);
	fmt::print(" namedpoint2; name: {0}, Point: [{1}, {2}, {3}]\n", namedpoint2.name, namedpoint2.pt.x, namedpoint2.pt.y, namedpoint2.pt.z);

	// Brace initialization ensure members are default initialized; in this case all zero
	// Brace initiliazation also prevents narrowing
	// Brace initialization also prevent vertex parsing; e.g : const Point3 pt3(); is seen as a function that return const Point3 with no arguments
	Point3D pt3DTwo{};
	fmt::print(" pt3DTwo: x:{}, y: {}, z:{}\n", pt3DTwo.x, pt3DTwo.y, pt3DTwo.z);

	// testing RVO for NonCopy or Movable class

}

inline void ReturnValueOptimization()
{
	std::printf("\n- ReturnValueOptimization-\n");
	auto myVal = Use();
	myVal.x = 25;

	fmt::print("Test call site Use creates NonCopyableorMovable x: {}\n", myVal.x);

	auto resVec = GetVectorPoint3d();
	std::puts("vec3d: ");
	for (const auto& Point : resVec)
	{
		fmt::print("[{}, {}, {}]\n", Point.x, Point.y, Point.z);
	}


	FileAccess({ .open = true });

}

