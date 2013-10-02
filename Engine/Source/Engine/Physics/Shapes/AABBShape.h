#pragma once

#include <Engine/Challenge.h>
#include "GeometricShape.h"
#include <Engine/Math/Ray.h>

#define EPSILON 0.001

namespace challenge
{
	class AABBShape : public GeometricShape
	{
	public:
		AABBShape() : GeometricShape() {}
		AABBShape(AABBShape *other);
		AABBShape(const glm::vec3 &center, real halfX, real halfY, real halfZ);
		AABBShape(const glm::vec3 &min, const glm::vec3 &max);
		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;
		bool RayIntersects(const Ray &ray, float &t) const;
		virtual glm::mat3 CalculateInertiaTensor(float mass);

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform);

		GeometricShapeType GetType() const { return kShapeTypeAABB; }
		glm::vec3 GetPosition() const { return mCenter + mPosition; }

		IGeometricShape* Clone();

		void SetDimensions(const glm::vec3 &dims)
		{
			mDimensions = dims;
			this->CalculateBoundingBox();
		}

		void SetHalfX(float halfX)
		{
			mDimensions.x = halfX;
			this->CalculateBoundingBox();
		}

		void SetHalfY(float halfY)
		{
			mDimensions.y = halfY;
			this->CalculateBoundingBox();
		}

		void SetHalfZ(float halfZ)
		{
			mDimensions.z = halfZ;
			this->CalculateBoundingBox();
		}

		const glm::vec3& GetDimensions() const { return mDimensions; }
		real GetHalfX() const { return mDimensions.x; }
		real GetHalfY() const { return mDimensions.y; }
		real GetHalfZ() const { return mDimensions.z; }

		void SetCenter(const glm::vec3 &center)
		{
			mCenter = center;
			this->CalculateBoundingBox();
		}

		void SetX(real x)
		{
			mCenter.x = x;
			this->CalculateBoundingBox();
		}

		void SetY(real y)
		{
			mCenter.y = y;
			this->CalculateBoundingBox();
		}

		void SetZ(real z)
		{
			mCenter.z = z;
			this->CalculateBoundingBox();
		}

		const glm::vec3& GetCenter() const { return mCenter; }
		real GetX() const { return mCenter.x; }
		real GetY() const { return mCenter.y; }
		real GetZ() const { return mCenter.z; }

	private:
		glm::vec3 mDimensions;
		glm::vec3 mCenter;

		void CalculateBoundingBox()
		{
			mBoundingBox.mMin.x = mDimensions.x - mCenter.x;
			mBoundingBox.mMin.y = mDimensions.y - mCenter.y;
			mBoundingBox.mMin.z = mDimensions.z - mCenter.z;
			mBoundingBox.mMax.x = mDimensions.x + mCenter.x;
			mBoundingBox.mMax.y = mDimensions.y + mCenter.y;
			mBoundingBox.mMax.z = mDimensions.z + mCenter.z;
		}
	};
};