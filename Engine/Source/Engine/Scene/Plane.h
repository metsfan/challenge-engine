#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Plane
	{
	public:
		Plane(void);
		Plane(float a, float b, float c, float d);
		Plane(glm::vec4 vec);
		Plane(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

		void Initialize(glm::vec4 vec);

		float DistanceFrom(glm::vec3 point);

		bool Contains(glm::vec3 point);
		bool Contains(glm::vec3 point, float radius);

	private:
		glm::vec4 mPlaneVec;
		glm::vec3 mNormalVec;
		double mDist;
	};
};