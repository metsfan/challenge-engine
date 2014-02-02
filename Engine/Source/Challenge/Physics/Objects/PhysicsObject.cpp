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

		mTotalForce = glm::vec3(0);
	}

	void PhysicsObject::ResolveCollision(const CollisionData &collision)
	{
		this->SetPosition(mPosition + (collision.collisionNormal * collision.penetrationDepth));
	}

	bool PhysicsObject::CollidesWith(PhysicsObject *other, CollisionData *collision)
	{
		return other->mShape->Intersects(mShape, collision);
	}
};