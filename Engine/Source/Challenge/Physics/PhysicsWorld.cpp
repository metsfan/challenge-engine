#include <Challenge/Challenge.h>
#include "PhysicsWorld.h"
using namespace challenge;

PhysicsWorld::PhysicsWorld()
{
	mCollisionDetector = new CollisionDetector();
	mCollisionResolver = new CollisionResolver();
}

void PhysicsWorld::AddObject(IPhysicsObject *object)
{
	mCollisionDetector->AddObject(object);
}

void PhysicsWorld::AddRigidBody(RigidBody *body)
{
	mRigidBodies.push_back(body);
	mCollisionDetector->AddObject(body);
}


void PhysicsWorld::UpdateSimulation(real duration)
{
	if(mRigidBodies.size() > 0) {
		TRigidBodyList tmp(mRigidBodies.size());
		std::copy(mRigidBodies.begin(), mRigidBodies.begin() + mRigidBodies.size(), tmp.begin());

		this->ApplyGravity(duration);
		TRigidBodyList::iterator it = tmp.begin();

		while (it != tmp.end()) {
			RigidBody *body = (*it);
			body->Integrate(duration);

			++it;
		}
	}

	TCollisionDataList collisions = mCollisionDetector->FindCollisions();

	mCollisionResolver->ResolveCollisions(collisions, duration);

}

/* Private methods */

void PhysicsWorld::ApplyGravity(real duration)
{
	TRigidBodyList::iterator it = mRigidBodies.begin();

	while (it != mRigidBodies.end()) {
		RigidBody * body = (*it);
		mGravityForce->UpdateForce(body, duration);

		++it;
	}
}