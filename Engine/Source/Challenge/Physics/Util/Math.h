#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/PlaneShape.h>

namespace challenge
{
	class PhysicsMath
	{
	public:
		static float PointPlaneDistance(const glm::vec3 &point, const PlaneShape *plane);
	};
};