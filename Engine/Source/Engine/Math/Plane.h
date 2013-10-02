#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Plane
	{
	public:
		Plane() {}

		Plane(real a, real b, real c, real d) :
			mPlane(a, b, c, d),
			mNormal(a, b, c)
		{
		}

		Plane(glm::vec4 plane) :
			mPlane(plane),
			mNormal(plane)
		{
		}

		~Plane() {}

		const glm::vec3& GetNormal() const { return mNormal; }
		const real GetD() const { return mPlane.w; }
		const glm::vec4& GetPlane() const { return mPlane; }

	private:
		glm::vec4 mPlane;
		glm::vec3 mNormal;
	};
};