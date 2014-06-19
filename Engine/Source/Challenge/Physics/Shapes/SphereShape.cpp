#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include "SphereShape.h"

namespace challenge
{
	SphereShape::SphereShape(real radius) :
		GeometricShape(),
		mRadius(radius)
	{
		this->UpdateShape();
	}

	void SphereShape::UpdateShape()
	{
		if (mCollisionShape != NULL) {
			delete mCollisionShape;
		}

		mCollisionShape = new btSphereShape(mRadius);
	}
};
