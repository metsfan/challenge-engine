#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>

namespace challenge
{
	static const real kTerminalVelocity = 50;

	void PhysicsObject::Update(real seconds)
	{
		glm::vec3 frameAccel = mAcceleration + mTotalForce;

		mVelocity += frameAccel * seconds;
		mVelocity.y = glm::min(mVelocity.y, kTerminalVelocity);

		mPosition += mVelocity * seconds;

		mShape->SetPosition(mPosition);
	}

	void PhysicsObject::ResolveCollision(const CollisionData &collision)
	{
		this->SetPosition(mPosition + glm::vec3(0, collision.penetrationDepth, 0));
	}
};