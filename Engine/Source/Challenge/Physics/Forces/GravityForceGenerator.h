#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Forces/ForceGenerator.h>

namespace challenge
{
	class GravityForceGenerator : IForceGenerator
	{
	public:
		GravityForceGenerator(glm::vec3 gravity);

		virtual void ApplyForce(PhysicsObject *object, real duration);

	protected:
		glm::vec3 mGravity;
	};
};