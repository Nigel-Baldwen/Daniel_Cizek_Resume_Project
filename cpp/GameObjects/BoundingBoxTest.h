#pragma once

#include <vector>
#include <list>
#include "GameObjects/GameObject.h"
#include "GameObjects/AxesEnum.h"

// TODO :: This should ultimately be converted to a namespace.
ref class BoundingBoxTest
{
internal:
	BoundingBoxTest();

	// The return object for the axisOverlapTest
	std::list<std::pair<GameObject^, GameObject^>> objectsRequiringFurtherTesting;
	// Clearing the above for clean execution frames.
	void ResetObjectsRequiringFurtherTesting();
	// Checks a given axis at a time to discover overlapping objects
	std::list<std::pair<GameObject^, GameObject^>> axisOverlapTest(std::list<std::pair<float, GameObject^>> sortedPairs, Axes axis);
};