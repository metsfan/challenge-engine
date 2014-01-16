#pragma once

#include <Challenge/Challenge.h>
#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>

namespace challenge
{
	class CollisionDetector
	{
	public:
		CollisionDetector();

		void ResolveCollision(std::vector<PhysicsObject *> objects);
	};
};