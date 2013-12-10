#include <Challenge/Challenge.h>
#include "Triangle.h"

namespace challenge
{
	Triangle::Triangle()
	{
	}

	Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		mPoints[0] = p1;
		mPoints[1] = p2;
		mPoints[2] = p3;

		mNormal = glm::cross(p2 - p1, p3 - p1);
	}

	Triangle::~Triangle()
	{
	}
};