#include <Engine/Challenge.h>
#include "Contact.h"
#include <Engine/Physics/Objects/RigidBody.h>
using namespace challenge;

Contact::Contact()
{
	mObjects[0] = mObjects[1] = NULL;
}

void Contact::CalculateInternals(real duration)
{
	glm::vec3 xAxis = mContactNormal, yAxis, zAxis;

	if(abs(mContactNormal.x) > abs(mContactNormal.y)) {
		yAxis = glm::vec3(0.0, 1.0, 0.0);
	} else {
		yAxis = glm::vec3(1.0, 0.0, 0.0);
	}
	this->MakeOrthonormalBasis(&xAxis, &yAxis, &zAxis);

	mContactToWorld = glm::mat3(
		xAxis.x, yAxis.x, zAxis.x,
		xAxis.y, yAxis.y, zAxis.y,
		xAxis.z, yAxis.z, zAxis.z
	);
	mWorldToContact = glm::transpose(mContactToWorld);

	mRelativePositions[0] = mContactPoint - mObjects[0]->GetPosition();
	if(mObjects[1]) {
		mRelativePositions[1] = mContactPoint - mObjects[1]->GetPosition();
	}

	mContactVelocity = this->CalculateLocalVelocity(0, duration);
	if(mObjects[1]) {
		mContactVelocity -= this->CalculateLocalVelocity(1, duration);
	}

	mDesiredDeltaVelocity = this->CalculateDesiredVelocity(duration);
	mVelocityPerUnitImpulse = this->CalculateImplusePerUnit(duration);

	mImpulse = mContactToWorld * glm::vec3(mDesiredDeltaVelocity / mVelocityPerUnitImpulse, 0.0f, 0.0f);
}

real Contact::CalculateImplusePerUnit(real duration)
{
	glm::vec3 relativePosition = mRelativePositions[0];

	glm::vec3 deltaVelWorld = glm::cross(relativePosition, mContactNormal);
	deltaVelWorld = glm::cross(deltaVelWorld, relativePosition);

	real deltaVelocity = glm::dot(deltaVelWorld, mContactNormal) + mObjects[0]->GetMass();

	if(mObjects[1]) {
		relativePosition = mRelativePositions[1] - mObjects[1]->GetPosition(); 

		deltaVelWorld = glm::cross(relativePosition, mContactNormal);
		deltaVelWorld = glm::cross(deltaVelWorld, relativePosition);

		deltaVelocity += glm::dot(deltaVelWorld, mContactNormal) + mObjects[1]->GetMass();
	}

	return deltaVelocity;
}

real Contact::CalculateDesiredVelocity(real duration)
{
	real restitution = -1.0f;

	glm::vec3 relativePosition = mRelativePositions[0];

	/*glm::vec3 velocity = glm::cross(mObjects[0]->GetRotation(), relativePosition) + mObjects[0]->GetVelocity();
	glm::vec3 contactVelocity = mWorldToContact * velocity;
	
	real desiredVelocity = -contactVelocity.x * (1 + restitution);

	if(mObjects[1]) {
		relativePosition = mRelativePositions[1];

		velocity = glm::cross(mObjects[1]->GetRotation(), relativePosition) + mObjects[1]->GetVelocity();
		contactVelocity = mContactToWorld * velocity;
	
		desiredVelocity += -contactVelocity.x * (1 * restitution);
	}*/

	real velocityFromAcc = glm::dot(mObjects[0]->mLastFrameAcceleration, mContactNormal) * duration;
	
	if(mObjects[1]) {
		velocityFromAcc -= glm::dot(mObjects[1]->mLastFrameAcceleration, mContactNormal) * duration;
	}

	real desiredVelocity = -mContactVelocity.x - (1 + restitution) * (mContactVelocity.x - velocityFromAcc);

	return desiredVelocity;
}

void Contact::MakeOrthonormalBasis(glm::vec3 *x, glm::vec3 *y, glm::vec3 *z)
{
	glm::normalize(*x);
	*z = glm::cross(*x, *y);
	real len = glm::length(*z);
	if(len * len == 0.0) return;
	*y = glm::cross(*z, *x);
}

glm::vec3 Contact::CalculateLocalVelocity(int index, real duration)
{
	RigidBody *body = mObjects[index];

	glm::vec3 velocity = glm::cross(body->GetRotation(), mRelativePositions[index]);
	velocity += body->GetVelocity();

	glm::vec3 contactVelocity = mWorldToContact * velocity;

	return contactVelocity;
}

void Contact::SwapBodies()
{
	mContactNormal *= -1;
	RigidBody *tmp = mObjects[0];
	mObjects[0] = mObjects[1];
	mObjects[1] = tmp;
}