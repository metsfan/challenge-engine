#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/CharacterController.h>

namespace challenge
{
	CharacterController::CharacterController(btGhostObject *object) :
		mGhostObject(object)
	{
	}

	CharacterController::~CharacterController()
	{
	}

	void CharacterController::setWalkDirection(const btVector3& walkDirection)
	{
		mWalkDirection = walkDirection;
	}

	void CharacterController::setVelocityForTimeInterval(const btVector3& velocity, btScalar timeInterval)
	{

	}

	void CharacterController::reset(btCollisionWorld* collisionWorld)
	{

	}

	void CharacterController::warp(const btVector3& origin)
	{

	}

	void CharacterController::preStep(btCollisionWorld* collisionWorld)
	{

	}

	void CharacterController::playerStep(btCollisionWorld* collisionWorld, btScalar dt)
	{

	}

	bool CharacterController::canJump() const
	{
		return false;
	}

	void CharacterController::jump()
	{

	}

	bool CharacterController::onGround() const
	{
		return false;
	}

	void CharacterController::setUpInterpolate(bool value)
	{

	}
}