#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/PhysicsCore.h>
#include <Engine/Physics/Collision/CollisionData.h>

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