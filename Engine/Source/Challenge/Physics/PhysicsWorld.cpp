#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsWorld.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>

namespace challenge
{

	PhysicsWorld::PhysicsWorld()
	{
		// Build the broadphase
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();

		btVector3 worldMin(-1000, -1000, -1000);
		btVector3 worldMax(1000, 1000, 1000);
		btAxisSweep3* sweepBP = new btAxisSweep3(worldMin, worldMax);
		
		// Set up the collision configuration and dispatcher
		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

		// The actual physics solver
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

		// The world.
		mPhysicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		mPhysicsWorld->getDispatchInfo().m_allowedCcdPenetration = 0.001f;
	}

	void PhysicsWorld::AddObject(PhysicsObject *object, int collisionGroup, int collisionFilter)
	{
		mObjects.lock();

		mObjects.push_back(object);
		object->SetPhysicsWorld(mPhysicsWorld, collisionGroup, collisionFilter);

		mObjects.unlock();
	}

	void PhysicsWorld::SetGravity(const glm::vec3 &gravity) 
	{
		mPhysicsWorld->setGravity(ToBullet(gravity));
	}

	void PhysicsWorld::Update(uint32_t deltaMillis)
	{
		real duration = deltaMillis * 0.001;
		if (mObjects.size() > 0) {
			mObjects.lock();

			auto objects = mObjects;
			float fixedsubstep = 1.f / 1000.0f;
			mPhysicsWorld->stepSimulation(1.0f / 60.f, 10, fixedsubstep);
			mPhysicsWorld->debugDrawWorld();
			mObjects.unlock();

			for (PhysicsObject *object : mObjects) {
				object->Update(1.0f / 60.f);
			}
		}
	}

	PhysicsObject * PhysicsWorld::RayIntersection(const Ray &ray, glm::vec3 &intersectionPoint, int collisionMask)
	{
		mPhysicsWorld->updateAabbs();
		mPhysicsWorld->computeOverlappingPairs();

		btVector3 start = ToBullet(ray.GetOrigin());
		btVector3 end = ToBullet(ray.ValueAt(5000));

		btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
		rayCallback.m_collisionFilterGroup = kPhysicsObjectAllFilter;
		rayCallback.m_collisionFilterMask = collisionMask;
		rayCallback.m_flags |= btTriangleRaycastCallback::kF_FilterBackfaces;
		rayCallback.m_flags |= btTriangleRaycastCallback::kF_UseSubSimplexConvexCastRaytest;

		mPhysicsWorld->rayTest(start, end, rayCallback);
		if (rayCallback.hasHit()) {
			PhysicsObject *object = reinterpret_cast<PhysicsObject *>(rayCallback.m_collisionObject->getUserPointer());
			if (object) {
				intersectionPoint = FromBullet(rayCallback.m_hitPointWorld);
				return object;
			}
		}

		return NULL;
	}

	std::vector<PhysicsObject *> PhysicsWorld::GetCollisions(IGeometricShape *shape)
	{
		mPhysicsWorld->performDiscreteCollisionDetection();

		return std::vector<PhysicsObject *>();
	}
}
