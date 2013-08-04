#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/PhysicsShape.h>

namespace challenge
{
	class PlaneShape : public PhysicsShape
	{
	public:
		PlaneShape() : PhysicsShape() {}
		PlaneShape(glm::vec4 components);
		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL);

		PhysicsShapeType GetType() { return kShapeTypePlane; }

		glm::vec4 mComponents;
		glm::vec3 mNormal;
		real mDistance;
	};
};