#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include "SphereShape.h"

namespace challenge
{
	SphereShape::SphereShape(const glm::vec3 &center, real radius) :
		GeometricShape(),
		mRadius(radius),
		mCenter(center)
	{
		this->CalculateBoundingBox();
	}
};
