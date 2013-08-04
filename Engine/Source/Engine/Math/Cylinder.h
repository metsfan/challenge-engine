#pragma once

#include <Engine/Challenge.h>
#include <Engine/Math/Ray.h>

namespace challenge
{
	class Cylinder
	{
	public:
		glm::vec3 top, bottom;
		float r, s, m, height;

		Cylinder(glm::vec3 top, glm::vec3 bottom, float r, float s)
		{
			this->top = top;
			this->bottom = bottom;
			this->height = glm::distance(top, bottom);
			this->r = r;
			this->s = s;
			this->m = r / s;
		}
		Cylinder(std::vector<glm::vec3> points, glm::vec3 principalAxis, glm::vec3 secondaryAxis);

		bool Intersects(Ray ray, glm::vec3 &intersectionPoint);
	};
};