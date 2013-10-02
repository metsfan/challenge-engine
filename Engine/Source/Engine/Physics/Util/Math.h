#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/PlaneShape.h>

namespace challenge
{
	class PhysicsMath
	{
	public:
		static float PointPlaneDistance(const glm::vec3 &point, const PlaneShape *plane);
	};
};