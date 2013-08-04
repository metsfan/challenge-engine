#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/PhysicsWorld.h>
#include <Engine/Physics/Objects/RigidBody.h>
#include <Engine/Model/Model.h>
#include <Engine/Event/EventManager.h>
#include <Engine/View/Actor.h>
#include <boost/thread.hpp>

namespace challenge
{
	typedef struct {
		RigidBody *body;
		IActor *actor;
	} PhysicsActor;

	typedef std::map<ActorId, PhysicsActor> TPhysicsObjectList;

	class PhysicsManager : public IEventListener
	{
	public:
		PhysicsManager();

		void OnUpdate();
		RigidBody* AddModel(Model *model, bool isStatic);

		/* IEventListener methods */
		bool HandleEvent(IEventData *data);
		char const * GetName(void) { return "PhysicsManager"; }

		static void ThreadCallback(PhysicsManager *physicsManager);

	private:
		PhysicsWorld *mWorld;
		TPhysicsObjectList mObjects;
		std::thread *mThread;

		void ActorAdded(IActor *actor);
		void ActorMoved(IActor *actor);
	};
};