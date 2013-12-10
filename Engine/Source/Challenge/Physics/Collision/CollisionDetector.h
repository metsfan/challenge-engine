#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsCore.h>
#include <Challenge/Physics/Collision/CollisionData.h>

namespace challenge
{
	typedef std::vector<CollisionData *> TCollisionDataList;

	class CollisionDetector
	{
	public:
		CollisionDetector();

		void AddObject(IPhysicsObject *object);
		TCollisionDataList FindCollisions();

	private:
		TObjectList mObjects;
	};
};