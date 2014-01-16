#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class PhysicsObject
	{
	public:
		PhysicsObject() :
			mMass(0)
		{
		}

		~PhysicsObject()
		{
		}

		void SetPosition(const glm::vec3 &position) 
		{ 
			mPosition = position; 
			mShape->SetPosition(position);
		}
		const glm::vec3& GetPosition() { return mPosition; }

		void SetVelocity(const glm::vec3 &velocity) { mVelocity = velocity; }
		const glm::vec3& GetVelocity() { return mVelocity; }

		void SetAcceleration(const glm::vec3 &acceleration) { mAcceleration = acceleration; }
		const glm::vec3& GetAcceleration() { return mAcceleration; }

		void SetShape(IGeometricShape *shape) { mShape = shape; }
		IGeometricShape * GetShape() { return mShape; }

		void SetMass(real mass) { mMass = mass; }
		real GetMass() { return mMass; }
		bool HasInfiniteMass() { return mMass == INFINITY; }

		void ApplyForce(const glm::vec3 &force)
		{
			mTotalForce += force;
		}

		virtual bool CollidesWith(PhysicsObject *other, CollisionData *collision = NULL)
		{
			return other->mShape->Intersects(mShape, collision);
		}

		virtual void ResolveCollision(const CollisionData &collision);

		void Update(real seconds);
		void DrawDebug(IGraphicsDevice *device, RenderState &state)
		{
			mShape->DrawDebug(device, state);
		}

	private:
		glm::vec3 mPosition;
		glm::vec3 mVelocity;
		glm::vec3 mAcceleration;
		IGeometricShape *mShape;
		real mMass;

		glm::vec3 mTotalForce;
	};
};