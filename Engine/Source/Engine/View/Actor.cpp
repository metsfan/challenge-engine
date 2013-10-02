#include <Engine/Challenge.h>
#include <Engine/Event/Types/ActorEventData.h>
#include <Engine/GameApplication.h>
#include <Engine/Event/EventManager.h>
#include <Engine/Util/Util.h>

#include "Actor.h"
using namespace challenge;

Actor::Actor()
{
	mTransform = glm::mat4(1.0f);
	mId = Util::uuid_create();
	mNetworkId = Util::uuid_create();
	mScale = 1.0f;
}

Actor::~Actor()
{
}

void Actor::OnUpdate(int deltaMillis)
{
	glm::mat4 playerTransform = glm::mat4(1.0f);
	playerTransform = glm::translate(playerTransform, this->mPosition);
	playerTransform = glm::scale(playerTransform, glm::vec3(this->mScale));
	playerTransform = glm::rotate(playerTransform, this->mXAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	//playerTransform = glm::rotate(playerTransform, -this->mYAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	this->SetTransform(playerTransform);
	//mModel->SetNextFrame(30);
}

void Actor::RotateY(float angle)
{
	mTransform = glm::translate(mTransform, glm::vec3(0, angle, 0));
}

void Actor::SetPosition(glm::vec3 position) 
{
	mPosition = position; 
	ActorMovedEventData *eventData = new ActorMovedEventData(0);
	eventData->position = position;
	eventData->model = mModel;
	eventData->actor = this;

	//GameApplication::GetInstance()->GetEventManager()->FireEvent(eventData);
}

void Actor::SetTransform(glm::mat4 matrix) 
{ 
	mPosition = glm::vec3(matrix[3]);
	mTransform = matrix; 
}

/* INetworKObject methods */
void Actor::Serialize(std::stringstream &stream)
{
	//stream.write((char *)&mNetworkId, sizeof(int));
	//stream.write((char *)&mType, sizeof(int));
}

void Actor::Unserialize(std::stringstream &stream)
{

}
