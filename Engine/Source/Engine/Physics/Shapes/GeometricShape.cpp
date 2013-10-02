#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include <Engine/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	GeometricShape::GeometricShape(GeometricShape *other) :
		mPosition(other->mPosition),
		mBoundingBox(other->mBoundingBox)
	{
	}
};

