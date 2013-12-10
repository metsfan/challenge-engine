#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/PhysicsWorld.h>
#include <Challenge/Physics/Objects/RigidBody.h>
#include <Challenge/Model/Model.h>
#include <Challenge/Event/EventManager.h>
#include <Challenge/View/Actor.h>

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