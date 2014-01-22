#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>

namespace challenge
{
	class CharacterPhysicsObject : public PhysicsObject
	{
	public:
		CharacterPhysicsObject() :
			PhysicsObject()
		{
		}

		~CharacterPhysicsObject()
		{
		}

		virtual bool CollidesWith(PhysicsObject *other, CollisionData *collision = NULL);

		void SetMaxJumpHeight(real jumpHeight) { mMaxJumpHeight = jumpHeight; }
		void SetMaxClimbAngle(real climbAngle) { mMaxClimbAngle = climbAngle; }
		void SetMaxStepHeight(real stepHeight) { mStepHeight = stepHeight; }

		virtual void ResolveCollision(const CollisionData &collision);

	private:
		real mStepHeight;
		real mMaxJumpHeight;
		real mMaxClimbAngle;
	};
};