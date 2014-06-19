#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsWorld.h>

namespace challenge
{
	PhysicsWorld::PhysicsWorld()
	{
		// Build the broadphase
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();

		// Set up the collision configuration and dispatcher
		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

		// The actual physics solver
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

		// The world.
		mPhysicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	}

	void PhysicsWorld::AddObject(PhysicsObject *object)
	{
		mObjects.lock();

		mObjects.push_back(object);
		mPhysicsWorld->addRigidBody(object->mRigidBody);

		mObjects.unlock();
	}

	void PhysicsWorld::SetGravity(const glm::vec3 &gravity) 
	{
		mPhysicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
	}

	void PhysicsWorld::Update(uint32_t deltaMillis)
	{
		real duration = deltaMillis * 0.001;
		if (mObjects.size() > 0) {
			mObjects.lock();

			auto objects = mObjects;
			mPhysicsWorld->stepSimulation(duration);

			mObjects.unlock();

			for (PhysicsObject *object : mObjects) {
				object->Update(duration);
			}
		}
	}
}
