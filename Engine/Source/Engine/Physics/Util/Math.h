#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/PlaneShape.h>

namespace challenge
{
	class PhysicsMath
	{
	public:
		static float PointPlaneDistance(glm::vec3 point, PlaneShape *plane);
	};
};