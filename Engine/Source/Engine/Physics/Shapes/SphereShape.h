#pragma once

#include <Engine/Challenge.h>
#include "PhysicsShape.h"

namespace challenge
{
	class SphereShape : public PhysicsShape
	{
	public:
		SphereShape() : PhysicsShape() {}
		SphereShape(glm::vec3 center, real radius);
		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL);

		PhysicsShapeType GetType() { return kShapeTypeSphere; }
		glm::vec3 GetPosition() { return mCenter + mPosition; }

		real mRadius;
		glm::vec3 mCenter;
	};
};