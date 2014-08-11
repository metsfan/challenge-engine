#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

namespace challenge
{
	class CharacterPhysicsObject : public PhysicsObject
	{
	public:
		CharacterPhysicsObject(IGeometricShape *shape);

		~CharacterPhysicsObject()
		{
		}

		void SetPosition(const glm::vec3 &position);

		virtual bool CollidesWith(PhysicsObject *other, CollisionData *collision = NULL);

		void SetMaxJumpHeight(real jumpHeight) { mMaxJumpHeight = jumpHeight; }
		void SetMaxClimbAngle(real climbAngle) { mMaxClimbAngle = climbAngle; }
		void SetMaxStepHeight(real stepHeight) { mStepHeight = stepHeight; }

		virtual void ResolveCollision(const CollisionData &collision);

		void Update(real seconds);

	private:
		real mStepHeight;
		real mMaxJumpHeight;
		real mMaxClimbAngle;

		btPairCachingGhostObject *mGhostObject;
		btKinematicCharacterController *mCharacterController;

		void SetPhysicsWorld(btDiscreteDynamicsWorld *world, int collisionGroup = kPhysicsObjectDefaultGroup,
			int collisionFilter = kPhysicsObjectAllFilter);
	};
};