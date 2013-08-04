#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include "SphereShape.h"
using namespace challenge;

SphereShape::SphereShape(glm::vec3 center, real radius) :
	mRadius(radius), mCenter(center)
{
}

bool SphereShape::Intersects(IPhysicsShape *other, CollisionData *collision)
{
	return false;
}