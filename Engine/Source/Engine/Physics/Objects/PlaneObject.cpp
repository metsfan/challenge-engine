#include <Engine/Challenge.h>
#include "PlaneObject.h"
#include <Engine/Physics/Collision/CollisionData.h>
#include <Engine/Physics/Shapes/GeometricShape.h>
using namespace challenge;

PlaneObject::PlaneObject(glm::vec4 components) : PhysicsObject()
{
	mShape = new PlaneShape(components);
	mType = kObjectTypePlane;
}