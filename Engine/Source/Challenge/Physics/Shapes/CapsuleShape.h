#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	enum CapsuleAxis
	{
		CapsuleAxisX,
		CapsuleAxisZ
	};

	class CapsuleShape : public GeometricShape
	{
	public:
		CapsuleShape(real radius, real height, CapsuleAxis axis);
		~CapsuleShape();

		GeometricShapeType GetType() const { return kShapeTypeCapsule; }

	private:
		real mRadius;
		real mHeight;
		CapsuleAxis mAxis;

		void UpdateShape();
	};
};