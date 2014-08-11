#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsCore.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>
#include <Challenge/Physics/Forces/GravityForceGenerator.h>
#include <Challenge/Physics/Collision/CollisionDetector.h>
//#include <Challenge/Physics/Collision/CollisionResolver.h>

#include <btBulletDynamicsCommon.h>

namespace challenge
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();

		void SetGravity(const glm::vec3 &gravity);

		void AddObject(PhysicsObject *body, int collisionGroup = kPhysicsObjectDefaultGroup,
			int collisionFilter = kPhysicsObjectAllFilter);

		PhysicsObject * RayIntersection(const Ray &ray, glm::vec3 &intersectionPoint, int collisionMask = kPhysicsObjectAllFilter);

		std::vector<PhysicsObject *> GetCollisions(IGeometricShape *shape);

		void Update(uint32_t deltaMillis);

	private:
		btDiscreteDynamicsWorld *mPhysicsWorld;

		//CollisionDetector *mCollisionDetector;
		//CollisionResolver *mCollisionResolver;
		SafeObject<std::vector<PhysicsObject *>> mObjects;
		std::map<const btCollisionObject *, PhysicsObject *> mBulletObjectMap;
		//GravityForceGenerator *mGravityForce;
		//bool stopGravity;

		//void ApplyGravity(real duration);
	};
};