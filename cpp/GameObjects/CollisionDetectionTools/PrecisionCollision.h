#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Sphere.h"
#include "GameObjects/Cylinder.h"
#include "GameObjects/Face.h"
#include "GameObjects/RectangularPrism.h"

namespace PrecisionCollision {
	// The IsColliding is essentially just a public switch statement.
	// This is also the only public member at present, further
	// functionality is encapsulated within an anomynous namespace
	// found within PrecisionCollision.cpp
	bool IsColliding(GameObject^ ibb, GameObject^ obb);
};