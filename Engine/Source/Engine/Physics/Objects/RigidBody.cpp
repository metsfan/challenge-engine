#include <Engine/Challenge.h>
#include "RigidBody.h"
#include <Engine/Physics/Collision/CollisionData.h>
#include <Engine/Physics/Shapes/PhysicsShape.h>
using namespace challenge;

RigidBody::RigidBody(IPhysicsShape *shape) : PhysicsObject()
{
	mLinearDamping = 1;
	mAngularDamping = 1;
	mType = kObjectTypeRigidBody;
	mShape = shape;
}

void RigidBody::SetPosition(glm::vec3 position)
{
	PhysicsObject::SetPosition(position);
	mShape->SetPosition(position);
}

bool RigidBody::CollidesWith(IPhysicsObject *other, CollisionData *collision)
{
	return mShape->Intersects(other->GetShape(), collision);
}

void RigidBody::SetInertiaTensor(glm::mat3 inertiaTensor)
{
	mInverseInertiaTensor = glm::inverse(inertiaTensor);
}

void RigidBody::AddForce(glm::vec3 force)
{
	mForceAccum += force;
}

void RigidBody::AddForceAtPoint(glm::vec3 force, glm::vec3 point)
{
	glm::vec3 pt = point - mPosition;

	mForceAccum += force;
	mTorqueAccum += glm::cross(pt, force);
}

void RigidBody::ClearAccumulators()
{
	mForceAccum = glm::vec3(0.0, 0.0, 0.0);
	mTorqueAccum = glm::vec3(0.0, 0.0, 0.0);
}

void RigidBody::Integrate(real duration)
{
	mLastFrameAcceleration= mAcceleration + (mForceAccum * mInverseMass);
	glm::vec3 angularAcceleration = glm::transpose(mInverseInertiaTensorWorld) * mTorqueAccum;

	mVelocity += mLastFrameAcceleration * duration;
	mRotation += angularAcceleration * duration;

	mVelocity *= pow(mLinearDamping, duration);
	mRotation *= pow(mAngularDamping, duration);

	mPosition += mVelocity * duration;
	mOrientation = mOrientation + (mRotation * duration);

	this->CalculateDerivedData();
	this->ClearAccumulators();
}

/* Private Methods */

void RigidBody::CalculateDerivedData()
{
	// Normalize orientation
	glm::normalize(mOrientation);

	// Calculate transform matrix
	mTransformMatrix = glm::mat4_cast(mOrientation);
	mTransformMatrix[3] = glm::vec4(mPosition, 1.0f);

	// Calculate inverse inertia tensor in world coords
	mInverseInertiaTensor = glm::inverse(mShape->CalculateInertiaTensor(mMass));
	glm::mat3 basis = glm::mat3(mTransformMatrix);
	mInverseInertiaTensorWorld = basis * mInverseInertiaTensor;
}