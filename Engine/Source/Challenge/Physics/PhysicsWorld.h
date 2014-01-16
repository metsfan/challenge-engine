#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsCore.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>
#include <Challenge/Physics/Forces/GravityForceGenerator.h>
#include <Challenge/Physics/Collision/CollisionDetector.h>
//#include <Challenge/Physics/Collision/CollisionResolver.h>

namespace challenge
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();

		void SetGravity(glm::vec3 gravity) { 
			mGravityForce = new GravityForceGenerator(gravity); 
		} 

		void AddObject(PhysicsObject *body);

		void Update(uint32_t deltaMillis);

	private:
		CollisionDetector *mCollisionDetector;
		//CollisionResolver *mCollisionResolver;
		SafeObject<std::vector<PhysicsObject *>> mObjects;
		GravityForceGenerator *mGravityForce;
		bool stopGravity;

		void ApplyGravity(real duration);
	};
};