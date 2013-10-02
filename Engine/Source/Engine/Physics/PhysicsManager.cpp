#include <Engine/Challenge.h>
#include <Engine/View/Actor.h>
#include <Engine/Event/EventData.h>
#include <Engine/Event/Types/ActorEventData.h>
#include <Engine/GameApplication.h>
#include <Engine/Event/EventManager.h>
#include <Engine/Physics/Shapes/TriangleMeshShape.h>
#include <Engine/Physics/Shapes/ConcaveTriangleMeshShape.h>
#include <Engine/Physics/Objects/PlaneObject.h>
#include <Engine/Model/ModelMesh.h>
#include "PhysicsManager.h"
using namespace challenge;

PhysicsManager::PhysicsManager()
{
	mWorld = new PhysicsWorld();
	mWorld->SetGravity(glm::vec3(0.0, -30.0, 0.0));

	//PlaneObject *plane = new PlaneObject(glm::vec4(0.0f, 1.0f, 0.0f, 100.0f));
	//mWorld->AddObject(plane);			

	mThread = new std::thread(PhysicsManager::ThreadCallback, this);
}

void PhysicsManager::ThreadCallback(PhysicsManager *physicsManager)
{
	int desiredFPS = 60;
	int frameTime = 1000000000 / desiredFPS;

	while (true) {
		LARGE_INTEGER time1, time2;
		QueryPerformanceCounter(&time1);

		physicsManager->OnUpdate();

		QueryPerformanceCounter(&time2);

		int dif = frameTime - (time2.QuadPart - time1.QuadPart);
		if (dif > 0) {
			Sleep(dif * 0.000001);
		}
	}
}
 
RigidBody* PhysicsManager::AddModel(Model *model, bool isStatic)
{
	TriangleMeshShape *meshShape;
	float mass = isStatic ? 0.0f : 1.0f;

	if(!isStatic) {
		meshShape = new TriangleMeshShape();
	} else {
		meshShape = new ConcaveTriangleMeshShape();
	}

	/*TMeshList meshes = model->GetMeshes();
	TMeshList::iterator it = meshes.begin();
	while (it != meshes.end()) {
		ModelVertex *verts = (*it)->GetBuffer();
		int nVerts = (*it)->GetTotalFaces();
		for(int i = 0; i < nVerts; i+=3) {
			glm::vec3 p1 = glm::vec3(verts[i].position[0], verts[i].position[1], verts[i].position[2]);
			glm::vec3 p2 = glm::vec3(verts[i+1].position[0], verts[i+1].position[1], verts[i+1].position[2]);
			glm::vec3 p3 = glm::vec3(verts[i+2].position[0], verts[i+2].position[1], verts[i+2].position[2]);

			meshShape->AddTriangle(p1, p2, p3);
		}
		++it;
	}*/

	meshShape->CalculateDerivedData();

	RigidBody *meshBody = new RigidBody(meshShape);
	meshBody->SetMass(mass);

	mWorld->AddRigidBody(meshBody);

	return meshBody;
}

void PhysicsManager::OnUpdate()
{
	mWorld->UpdateSimulation(0.01667);

	TPhysicsObjectList::iterator it = mObjects.begin();
	while (it != mObjects.end()) {
		IActor *actor = it->second.actor;                               
		RigidBody *body = it->second.body;

		actor->SetPosition(body->GetPosition());

		++it;
	}
}

/* Private Methods */

void PhysicsManager::ActorAdded(IActor *actor)
{
	RigidBody *meshBody = AddModel(actor->GetModel(), false);
	meshBody->SetPosition(actor->GetPosition());
	//meshBody->SetOrientation(actor->GetAngle());

	PhysicsActor obj;
	obj.body = meshBody;
	obj.actor = actor;
	mObjects[actor->GetId()] = obj;
}

void PhysicsManager::ActorMoved(IActor *actor)
{
	RigidBody *body = mObjects[actor->GetId()].body;
	body->SetPosition(actor->GetPosition());
}

/* IEventListener methods */
bool PhysicsManager::HandleEvent(IEventData *data)
{
	std::string eventType = data->GetEventType();
	if(eventType == "actor_added") {
		ActorEventData *charEventData = static_cast<ActorEventData *>(data);
		this->ActorAdded(charEventData->actor);
	} else if(eventType == "actor_moved") {
		ActorEventData *charEventData = static_cast<ActorEventData *>(data);
		this->ActorMoved(charEventData->actor);
	}
	return true;
}