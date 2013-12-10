#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsCore.h>
#include <Challenge/Physics/Forces/GravityForceGenerator.h>
#include <Challenge/Physics/Collision/CollisionDetector.h>
#include <Challenge/Physics/Collision/CollisionResolver.h>

namespace challenge
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();

		void SetGravity(glm::vec3 gravity) { 
			mGravityForce = new GravityForceGenerator(gravity); 
		} 

		void AddObject(IPhysicsObject *body);
		void AddRigidBody(RigidBody *body);

		void UpdateSimulation(real duration);

	private:
		CollisionDetector *mCollisionDetector;
		CollisionResolver *mCollisionResolver;
		TRigidBodyList mRigidBodies;
		GravityForceGenerator *mGravityForce;
		bool stopGravity;

		void ApplyGravity(real duration);
	};
};