#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Math/Triangle.h>
#include <Challenge/Math/Plane.h>

namespace challenge
{
	enum RayCastType
	{
		RayCastClosest,
		RayCastFurthes
	};

	class Ray
	{
	public:
		Ray(glm::vec3 origin, glm::vec3 direction) :
			mOrigin(origin),
			mDirection(direction)
		{
		}

		glm::vec3 ValueAt(float t) const 
		{
			return mOrigin + (mDirection * t);
		}

		const glm::vec3& GetOrigin() const { return mOrigin; }
		real GetOriginX() const { return mOrigin.x; }
		real GetOriginY() const { return mOrigin.y; }
		real GetOriginZ() const { return mOrigin.z; }

		void SetOrigin(const glm::vec3 &origin) { mOrigin = origin; }
		void SetOriginX(real x) { mOrigin.x = x; }
		void SetOriginY(real y) { mOrigin.y = y; }
		void SetOriginZ(real z) { mOrigin.z = z; }

		const glm::vec3& GetDirection() const { return mDirection; }
		real GetDirectionX() const { return mDirection.x; }
		real GetDirectionY() const { return mDirection.y; }
		real GetDirectionZ() const { return mDirection.z; }

		void Direction(const glm::vec3 &direction) { mDirection = direction; }
		void SetDirectionX(real x) { mDirection.x = x; }
		void SetDirectionY(real y) { mDirection.y = y; }
		void SetDirectionZ(real z) { mDirection.z = z; }

		bool GetIntersection(const BoundingBox &bounds, float &t) const;
		bool GetIntersection(const Triangle &triangle, float &t) const;
		bool GetIntersection(const Plane &plane, float &t) const;

	private:
		glm::vec3 mOrigin;
		glm::vec3 mDirection;
	};
};