#include <Engine/Challenge.h>
#include "PhysicsCore.h"
#include <Engine/Physics/Shapes/PhysicsShape.h>
using namespace challenge;

IPhysicsShape* PhysicsObject::GetShape()
{
	return mShape;
}


void PhysicsObject::SetMass(real mass)
{
	mMass = mass;
	if(mass == 0) {
		mInverseMass = 0;
	} else {
		mInverseMass = 1.0 / mass;
	}
}

void PhysicsObject::FireCollisionCallbacks(IPhysicsObject *otherObj)
{
	for(int i = 0; i < mCollisionCallbacks.size(); i++) {
		TCollisionCallback *callback = mCollisionCallbacks[i];
		(*callback)(this, otherObj);
	}
}