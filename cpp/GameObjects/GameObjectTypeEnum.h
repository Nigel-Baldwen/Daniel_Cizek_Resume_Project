#pragma once

enum class GameObjectType
{
	Sphere, Cylinder, Face, RectangularPrism, UNKNOWN
};

// TODO :: Consider whether or not this is too sketchy

// Forward declaration of all GameObject ref classes so that
// we get easy access to handles in subclasses of GameObject
// Particularly sketchy in light of the fact that GameObject.h
// itself #includes this class. So...maybe not the smartest thing
// to be doing.

ref class Sphere;
ref class Face;
ref class Cylinder;
ref class RectangularPrism;