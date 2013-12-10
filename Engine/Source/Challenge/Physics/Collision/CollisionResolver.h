#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Collision/CollisionDetector.h>

namespace challenge
{
	class CollisionResolver
	{
	public:
		CollisionResolver();

		void ResolveCollisions(TCollisionDataList collisions, real duration);

	private:

		void ApplyVelocityChanges(Contact *data, glm::vec3 impulse);
		void ApplyPositionChanges(Contact *data);
	};
};