#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>

namespace challenge
{
	static const real kTerminalVelocity = 50;

	PhysicsObject::PhysicsObject(IGeometricShape *shape) :
		mMass(0),
		mRigidBody(NULL)
	{
		this->SetShape(shape);
	}

	void PhysicsObject::Update(real seconds)
	{
		if (mAcceleration != glm::vec3()) {
			mRigidBody->applyCentralForce(ToBullet(mAcceleration));
		}

		if (mVelocity != glm::vec3()) {
			mRigidBody->setLinearVelocity(ToBullet(mVelocity));
		}

		btTransform trans;
		mMotionState->getWorldTransform(trans);
		btVector3 position = trans.getOrigin();

		mPosition = glm::vec3(position.x(), position.y(), position.z());
		mShape->SetPosition(mPosition);
		mRigidBody->setWorldTransform(trans);
	}

	void PhysicsObject::SetTransform(const glm::mat4 &transform)
	{
		mTransform = transform;
		mShape->SetTransform(transform);

		if (mRigidBody) {
			btMatrix3x3 basis(
				transform[0][0], transform[0][1], transform[0][2],
				transform[1][0], transform[1][1], transform[1][2],
				transform[2][0], transform[2][1], transform[2][2]
				);
			btVector3 position(transform[3][0], transform[3][1], transform[3][2]);
			btTransform btTransform(btTransform(basis, ToBullet(mPosition)));
			mRigidBody->setWorldTransform(btTransform);
		}
	}

	void PhysicsObject::ResolveCollision(const CollisionData &collision)
	{
		this->SetPosition(mPosition + (collision.collisionNormal * collision.penetrationDepth));
	}

	bool PhysicsObject::CollidesWith(PhysicsObject *other, CollisionData *collision)
	{
		return other->mShape->Intersects(mShape, collision);
	}

	void PhysicsObject::SetMass(real mass)
	{
		mMass = mass;

		if (mRigidBody) {
			mRigidBody->setMassProps(mass, btVector3());
		}
	}

	void PhysicsObject::SetPosition(const glm::vec3 &position)
	{
		mPosition = position;
		mShape->SetPosition(position);

		if (mRigidBody) {
			btTransform transform(btTransform(btQuaternion(0, 0, 0, 1), ToBullet(mPosition)));
			mRigidBody->setWorldTransform(transform);
			mMotionState->setWorldTransform(transform);
		}
	}

	void PhysicsObject::SetShape(IGeometricShape *shape)
	{
		mShape = shape;

		if (shape) {
			mPosition = shape->GetPosition();
		}
	}

	void PhysicsObject::SetPhysicsWorld(btDiscreteDynamicsWorld *world, int collisionGroup, int collisionFilter)
	{
		btTransform transform(btTransform(btQuaternion(0, 0, 0, 1), ToBullet(mPosition)));

		mMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo objInfo(mMass, mMotionState, mShape->GetBulletShape());
		mRigidBody = new btRigidBody(objInfo);

		mRigidBody->setUserPointer(this);

		world->addRigidBody(mRigidBody, collisionGroup, collisionFilter);
	}

};