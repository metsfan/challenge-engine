#pragma once

#include <Challenge/Challenge.h>

#include <btBulletCollisionCommon.h>
#include <BulletDynamics/Character/btCharacterControllerInterface.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace challenge
{
	class CharacterController : public btCharacterControllerInterface
	{
	public:
		CharacterController(btGhostObject *object);
		~CharacterController();

		void setWalkDirection(const btVector3& walkDirection);
		void setVelocityForTimeInterval(const btVector3& velocity, btScalar timeInterval);
		void reset(btCollisionWorld* collisionWorld);
		void warp(const btVector3& origin);

		void preStep(btCollisionWorld* collisionWorld);
		void playerStep(btCollisionWorld* collisionWorld, btScalar dt);
		bool canJump() const;
		void jump();

		bool onGround() const;
		void setUpInterpolate(bool value);

	private:
		btGhostObject *mGhostObject;
		btVector3 mWalkDirection;
		btVector3 mPosition;
	};
};