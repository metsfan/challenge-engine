#pragma once

#include <Challenge/Challenge.h>
#include "GeometricShape.h"

namespace challenge
{
	class SphereShape : public GeometricShape
	{
	public:
		SphereShape() : GeometricShape() {}
		SphereShape(const glm::vec3 &center, real radius);

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

		virtual bool Intersects(const IGeometricShape *other, CollisionData *collision = NULL) const
		{
			return other->Intersects(this, collision);
		}

		virtual bool Intersects(const AABBShape *aabb, CollisionData *collision = NULL) const
		{
			return IntersectionTests::AABBIntersectsSphere(aabb, this, collision);
		}

		virtual bool Intersects(const OBBShape *obb, CollisionData *collision = NULL) const
		{
			//return IntersectionTests::OBBIntersectsSphere(obb, this, collision);
			return false;
		}

		virtual bool Intersects(const TriangleShape *triangle, CollisionData *collision = NULL) const
		{
			//return IntersectionTests::SphereIntersectsTriangle(this, triangle, collision);
			return false;
		}

		virtual bool Intersects(const TriangleMeshShape *mesh, CollisionData *collision = NULL) const
		{
			return mesh->Intersects(this, collision);
		}

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