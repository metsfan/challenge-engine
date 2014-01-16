#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include "SphereShape.h"

namespace challenge
{
	SphereShape::SphereShape(glm::vec3 center, real radius) :
		mRadius(radius),
		mCenter(center)
	{
	}

	bool SphereShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		return false;
	}
};
