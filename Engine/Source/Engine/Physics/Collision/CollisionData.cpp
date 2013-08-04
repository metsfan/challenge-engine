#include <Engine/Challenge.h>
#include "CollisionData.h"
#include <Engine/Physics/Objects/RigidBody.h>
using namespace challenge;

CollisionData::CollisionData()
{
}

void CollisionData::CalculateInternals(real duration)
{
	for(int i = 0; i < mContacts.size(); i++) {
		mContacts[i]->CalculateInternals(duration);
	}
}