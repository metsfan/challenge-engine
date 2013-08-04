#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class MathUtil
	{
	public:
		static float ScalarTriple(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3);
		static int Sign(float val);
		static float GetLookAtAngle(glm::vec3 v1, glm::vec3 v2);
		static glm::vec3 WorldCoordFromScreenCoord(glm::vec2 screenCoord, float depth);
		static glm::vec2 ScreenCoordFromWorldCoord(glm::vec3 worldCoord);
		static int NearestPow2(int v);
	};
};