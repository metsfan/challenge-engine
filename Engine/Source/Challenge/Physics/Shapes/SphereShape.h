#pragma once

#include <Challenge/Challenge.h>
#include "GeometricShape.h"

namespace challenge
{
	class SphereShape : public GeometricShape
	{
	public:
		SphereShape() : GeometricShape() {}
		SphereShape(real radius);

		GeometricShapeType GetType() const { return kShapeTypeSphere; }

		void SetRadius(real radius)
		{
			mRadius = radius;
			this->UpdateShape();
		}

		real GetRadius() const { return mRadius; }

	private:
		real mRadius;

		void UpdateShape();
	};
};