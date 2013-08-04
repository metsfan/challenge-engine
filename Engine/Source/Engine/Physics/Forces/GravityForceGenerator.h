#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Forces/ForceGenerator.h>

namespace challenge
{
	class GravityForceGenerator : IForceGenerator
	{
	public:
		GravityForceGenerator(glm::vec3 gravity);

		virtual void UpdateForce(RigidBody *body, real duration);

	protected:
		glm::vec3 mGravity;
	};
};