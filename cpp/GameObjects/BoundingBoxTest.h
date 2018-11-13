#pragma once

#include <list>

ref class BoundingBoxTest
{
internal:
	BoundingBoxTest();

	std::list<std::list<int>> axisOverlapTest(std::list<std::pair<float, int>>);
};