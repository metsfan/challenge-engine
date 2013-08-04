#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/PhysicsCore.h>
#include <Engine/Physics/Shapes/PhysicsShape.h>
#include <glm/gtc/quaternion.hpp>

namespace challenge
{
	class RigidBody : public PhysicsObject
	{
	public:
		RigidBody(IPhysicsShape *shape);

		bool CollidesWith(IPhysicsObject *other, CollisionData *collision = NULL);

		void SetInertiaTensor(glm::mat3 inertiaTensor);
		
		virtual void Integrate(real duration);

		void AddForce(glm::vec3 force);
		void AddForceAtPoint(glm::vec3 force, glm::vec3 point);
		void ClearAccumulators();

		void SetOrientation(float angle) { mOrientation = glm::rotate(glm::quat(), angle, glm::vec3(0.0f, 1.0f, 0.0f)); }
		glm::quat GetOrientation() { return mOrientation; }

		glm::vec3 GetRotation() { return mRotation; }
		void SetRotation(glm::vec3 rotation) { mRotation = rotation; }

		glm::vec3 GetVelocity() { return mVelocity; }
		void SetVelocity(glm::vec3 velocity) { mVelocity = velocity; }

		void SetPosition(glm::vec3 position);

		real mLinearDamping;
		real mAngularDamping;
	
		glm::vec3 mLastPosition;
		glm::quat mOrientation;
		glm::vec3 mVelocity;
		glm::vec3 mRotation;
		glm::vec3 mAcceleration;
		glm::vec3 mLastFrameAcceleration;
		glm::mat4 mTransformMatrix;
		glm::mat3 mInverseInertiaTensor;
		glm::mat3 mInverseInertiaTensorWorld;
		glm::vec3 mForceAccum;
		glm::vec3 mTorqueAccum;

	protected:
		virtual void CalculateDerivedData();
	};
};