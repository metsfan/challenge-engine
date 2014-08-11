#pragma once

#include <Challenge/Challenge.h>

#include <btBulletDynamicsCommon.h>

namespace challenge
{
	enum PhysicsObjectFlags
	{
		PhysicsObjectFlagNoGravity = (1 << 1)
	};

	static const int kPhysicsObjectDefaultGroup = btBroadphaseProxy::DefaultFilter;
	static const int kPhysicsObjectAllFilter = btBroadphaseProxy::AllFilter;

	class PhysicsObject
	{
		friend class PhysicsWorld;

	public:
		PhysicsObject() :
			PhysicsObject(NULL)
		{
		}

		PhysicsObject(IGeometricShape *shape);

		~PhysicsObject()
		{
		}

		virtual void SetPosition(const glm::vec3 &position);

		void MoveBy(const glm::vec3 &delta)
		{
			this->SetPosition(mPosition + delta);
		}

		const glm::vec3& GetPosition() { return mPosition; }

		void SetVelocity(const glm::vec3 &velocity) { mVelocity = velocity; }
		const glm::vec3& GetVelocity() { return mVelocity; }

		void SetAcceleration(const glm::vec3 &acceleration) { mAcceleration = acceleration; }
		const glm::vec3& GetAcceleration() { return mAcceleration; }

		void SetShape(IGeometricShape *shape);
		IGeometricShape * GetShape() { return mShape; }

		void SetTransform(const glm::mat4 &transform);
		const glm::mat4& GetTransform() { return mTransform; }

		void SetMass(real mass);
		real GetMass() { return mMass; }
		bool HasInfiniteMass() { return mMass == INFINITY; }

		void ApplyForce(const glm::vec3 &force)
		{
			mTotalForce += force;
		}

		virtual bool CollidesWith(PhysicsObject *other, CollisionData *collision = NULL);

		virtual void ResolveCollision(const CollisionData &collision);

		virtual void Update(real seconds);
		void DrawDebug(IGraphicsDevice *device, RenderState &state)
		{
			mShape->DrawDebug(device, state);
		}

		virtual void SetPhysicsWorld(btDiscreteDynamicsWorld *world, int collisionGroup = kPhysicsObjectDefaultGroup,
			int collisionFilter = kPhysicsObjectAllFilter);

		void SetUserData(void *ptr)
		{
			mUserData = ptr;
		}

		void * GetUserData() { return mUserData; }

		void SetFlags(uint32_t flags) { mFlags = flags; }
		uint32_t GetFlags() { return mFlags; }

	protected:
		glm::vec3 mPosition;
		glm::vec3 mVelocity;
		glm::vec3 mAcceleration;
		glm::mat4 mTransform;
		IGeometricShape *mShape;
		real mMass;

		uint32_t mFlags;

		glm::vec3 mTotalForce;

		btRigidBody *mRigidBody;
		btMotionState *mMotionState;

		void *mUserData;
	};
};