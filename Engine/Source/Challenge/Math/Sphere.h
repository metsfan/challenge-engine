#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Sphere
	{
	public:
		Sphere(const glm::vec3 &position = glm::vec3(), real radius = 0) :
			mPosition(position),
			mRadius(radius)
		{
		}

		~Sphere() {}

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(glm::vec3 val) { mPosition = val; }

		real GetRadius() const { return mRadius; }
		void SetRadius(real val) { mRadius = val; }

		bool Contains(const glm::vec3 &point) const
		{
			return glm::distance(point, mPosition) <= mRadius;
		}

	private:
		glm::vec3 mPosition;
		real mRadius;
		
	};
};