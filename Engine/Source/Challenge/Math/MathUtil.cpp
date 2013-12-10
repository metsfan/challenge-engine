#include <Challenge/Challenge.h>
#include "MathUtil.h"

namespace challenge
{
	float MathUtil::ScalarTriple(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3)
	{
		glm::vec3 cross = glm::cross(v1, v2);
		double dot = glm::dot(v3, cross);
		return dot;
	}

	int MathUtil::Sign(float val)
	{
		return (val > 0 ? 1 : (val < 0 ? -1 : 0));
	}

	float MathUtil::GetLookAtAngle(glm::vec3 v1, glm::vec3 v2)
	{
		glm::vec3 dif = v1 - v2;

		float angle = atan2(dif.x, dif.z);

		return glm::degrees(angle) + 180;
	}

	glm::vec3 MathUtil::WorldCoordFromScreenCoord(glm::vec2 screenCoord, float depth)
	{
		return glm::vec3();
	}

	glm::vec2 MathUtil::ScreenCoordFromWorldCoord(glm::vec3 worldCoord)
	{
		glm::vec2 point;
		point.x = (-1.0f / worldCoord.z) * worldCoord.x;
		point.y = (-1.0f / worldCoord.z) * worldCoord.y;
		return point;
	}

	 int MathUtil::NearestPow2(int v)
	 {
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;

		return v;
	 }
};