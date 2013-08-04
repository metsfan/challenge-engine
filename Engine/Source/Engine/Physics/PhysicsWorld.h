#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/PhysicsCore.h>
#include <Engine/Physics/Forces/GravityForceGenerator.h>
#include <Engine/Physics/Collision/CollisionDetector.h>
#include <Engine/Physics/Collision/CollisionResolver.h>

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