#pragma once

#include <Engine/Challenge.h>
#include "GeometricShape.h"

namespace challenge
{
	class SphereShape : public GeometricShape
	{
	public:
		SphereShape() : GeometricShape() {}
		SphereShape(glm::vec3 center, real radius);
		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;

		GeometricShapeType GetType() const { return kShapeTypeSphere; }
		glm::vec3 GetPosition() const { return mCenter + mPosition; }

		void SetRadius(real radius)
		{
			mRadius = radius;
			this->CalculateBoundingBox();
		}

		real GetRadius() const { return mRadius; }

		void SetCenter(const glm::vec3 &center)
		{
			mCenter = center;
			this->CalculateBoundingBox();
		}

		const glm::vec3& GetCenter() const { return mCenter; }

	private:
		real mRadius;
		glm::vec3 mCenter;

		void CalculateBoundingBox()
		{
			mBoundingBox.mMin.x = mCenter.x - mRadius;
			mBoundingBox.mMin.y = mCenter.y - mRadius;
			mBoundingBox.mMin.z = mCenter.z - mRadius;
			mBoundingBox.mMax.x = mCenter.x + mRadius;
			mBoundingBox.mMax.y = mCenter.y + mRadius;
			mBoundingBox.mMax.z = mCenter.z + mRadius;
		}
	};
};