#pragma once

#include <list>
#include "GameObjects/GameObject.h"
#include "Core/Simple3DGame.h"

ref class BoundingBoxTest
{
internal:
	BoundingBoxTest();
	
	// The return object for the axisOverlapTest
	std::list<std::pair<GameObject^, GameObject^>> objectsRequiringFurtherTesting;
	// Checks a given axis at a time to discover overlapping objects
	std::list<std::pair<GameObject^, GameObject^>> axisOverlapTest(std::list<std::pair<float, GameObject^>> sortedPairs, Simple3DGame::Axes axis);
};