#pragma once

#include <Engine/Challenge.h>
#include <Engine/Math/Triangle.h>

namespace challenge
{
	class Ray
	{
	public:
		Ray(glm::vec3 origin, glm::vec3 direction) :
			mOrigin(origin),
			mDirection(direction)
		{
		}

		glm::vec3 ValueAt(float t)
		{
			return mOrigin + (mDirection * t);
		}

		bool GetIntersection(const Triangle &triangle, float &t) const;

	private:
		glm::vec3 mOrigin;
		glm::vec3 mDirection;
	};
};