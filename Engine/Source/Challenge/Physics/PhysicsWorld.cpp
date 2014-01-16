#include <Challenge/Challenge.h>
#include "PhysicsWorld.h"
using namespace challenge;

PhysicsWorld::PhysicsWorld()
{
	mCollisionDetector = new CollisionDetector();
	//mCollisionResolver = new CollisionResolver();
	mGravityForce = new GravityForceGenerator(glm::vec3(0, -9.81, 0));
}

void PhysicsWorld::AddObject(PhysicsObject *object)
{
	mObjects.lock();
	mObjects.push_back(object);
	mObjects.unlock();

	//mCollisionDetector->AddObject(object);
}


void PhysicsWorld::Update(uint32_t deltaMillis)
{
	real duration = deltaMillis * 0.001;
	if(mObjects.size() > 0) {
		mObjects.lock();
		auto objects = mObjects;
		mObjects.unlock();

		this->ApplyGravity(duration);
		for (PhysicsObject *object : mObjects) {
			object->Update(duration);
		}
	}

	mCollisionDetector->ResolveCollision(mObjects);
	//TCollisionDataList collisions = mCollisionDetector->FindCollisions();

	//mCollisionResolver->ResolveCollisions(collisions, duration);

}

/* Private methods */

void PhysicsWorld::ApplyGravity(real duration)
{
	for (PhysicsObject *object : mObjects) {
		mGravityForce->ApplyForce(object, duration);
	}
}