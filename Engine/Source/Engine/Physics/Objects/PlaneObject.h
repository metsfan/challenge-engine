#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/PhysicsCore.h>
#include <Engine/Physics/Shapes/PlaneShape.h>

namespace challenge
{
	class PlaneObject : public PhysicsObject
	{
	public:
		PlaneObject(glm::vec4 components);

		bool CollidesWith(IPhysicsObject *other, CollisionData *collision = NULL) { return false; }

		glm::vec4 GetComponents() { return static_cast<PlaneShape *>(mShape)->mComponents; }
		glm::vec3 GetNormal() { return static_cast<PlaneShape *>(mShape)->mNormal; }
		real GetDistance() { return static_cast<PlaneShape *>(mShape)->mDistance; }
	};
};