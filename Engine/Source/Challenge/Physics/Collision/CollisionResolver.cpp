#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/RigidBody.h>
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
