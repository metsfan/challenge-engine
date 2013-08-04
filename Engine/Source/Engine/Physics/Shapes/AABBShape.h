#pragma once

#include <Engine/Challenge.h>
#include "PhysicsShape.h"
#include <Engine/Math/Ray.h>

#define EPSILON 0.001

namespace challenge
{
	class AABBShape : public PhysicsShape
	{
	public:
		AABBShape() : PhysicsShape() {}
		AABBShape(glm::vec3 center, real halfX, real halfY, real halfZ);
		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL);
		bool RayIntersects(Ray ray, glm::vec3 *outPoint = NULL);
		virtual glm::mat3 CalculateInertiaTensor(float mass);
		virtual BoundingBox GetBoundingBox();

		PhysicsShapeType GetType() { return kShapeTypeAABB; }
		glm::vec3 GetPosition() { return mCenter + mPosition; }

		real mHalfX, mHalfY, mHalfZ;
		glm::vec3 mCenter;

	};
};