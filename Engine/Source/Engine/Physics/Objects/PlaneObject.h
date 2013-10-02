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

		glm::vec3 GetNormal() { return static_cast<PlaneShape *>(mShape)->GetNormal(); }
		real GetDistance() { return static_cast<PlaneShape *>(mShape)->GetD(); }
	};
};