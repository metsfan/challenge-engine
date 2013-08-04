#include <Engine/Challenge.h>
#include <Engine/Physics/Objects/RigidBody.h>
#include "CollisionResolver.h"
using namespace challenge;

CollisionResolver::CollisionResolver()
{
}

void CollisionResolver::ResolveCollisions(TCollisionDataList collisions, real duration)
{
	for(int i = 0; i < collisions.size(); i++) {
		CollisionData *data = collisions[i];
		
		for(int j = 0; j < data->mContacts.size(); j++) {
			Contact *contact = data->mContacts[j];
			contact->CalculateInternals(duration);
			ApplyPositionChanges(contact);
			ApplyVelocityChanges(contact, contact->mImpulse);
			
		}
	}
}

void CollisionResolver::ApplyVelocityChanges(Contact *data, glm::vec3 impulse)
{
	glm::vec3 velocityChange = impulse * data->mObjects[0]->GetMass();
	glm::vec3 impulsiveTorque(0.0, 0.0, 0.0);
	glm::vec3 rotationChange(0.0, 0.0, 0.0);
	
	// Hack to force velocity in only y direction
	velocityChange *= glm::vec3(0.0, 1.0, 0.0);

	data->mObjects[0]->SetVelocity(data->mObjects[0]->GetVelocity() + velocityChange);

	if(data->mObjects[1]) {
		impulse *= -1;
		velocityChange = impulse * data->mObjects[1]->GetMass();

		data->mObjects[1]->SetVelocity(data->mObjects[1]->GetVelocity() + velocityChange);
	}
}

void CollisionResolver::ApplyPositionChanges(Contact *data)
{
	// TODO: Implement angular position change.
	real penetration = 0.8f;
	real totalInertia = 0;
	real linearInertia[2], angularInertia[2], linearMove[2];
 	for(int i = 0; i < 2; i++) {
		if(data->mObjects[i]) {
			glm::vec3 angularInertiaWorld = glm::cross(data->mRelativePositions[i], data->mContactNormal);
			angularInertiaWorld = data->mObjects[i]->mInverseInertiaTensor * angularInertiaWorld;
			angularInertiaWorld = glm::cross(angularInertiaWorld, data->mRelativePositions[i]);
			angularInertia[i] = glm::dot(angularInertiaWorld, data->mContactNormal);

			linearInertia[i] = data->mObjects[i]->GetMass();
			totalInertia += linearInertia[i] + angularInertia[i];
		}
	}

	real inverseInertia = 1 / totalInertia;
	linearMove[0] = data->mPenetration * linearInertia[0] * inverseInertia;
	linearMove[1] = -data->mPenetration * linearInertia[1] * inverseInertia;

	for(int i = 0; i < 2; i++) {
		if(data->mObjects[i]) {
			glm::vec3 position = data->mObjects[i]->GetPosition();
			glm::vec3 delta = (data->mContactNormal * linearMove[i]);
			data->mObjects[i]->SetPosition(position + delta);
		}
	}
}
