#include <Challenge/Challenge.h>
#include "PlaneObject.h"
#include <Challenge/Physics/Collision/CollisionData.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>
using namespace challenge;

PlaneObject::PlaneObject(glm::vec4 components) : PhysicsObject()
{
	mShape = new PlaneShape(components);
	mType = kObjectTypePlane;
}