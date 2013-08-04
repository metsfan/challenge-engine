#pragma once

#include <Engine/Challenge.h>
#include <Engine/Event/EventData.h>
#include <Engine/Model/Model.h>
#include <Engine/View/Actor.h>
using namespace challenge;

static const std::string kActorAddedEventType = "actor_added";
static const std::string kActorMovedEventType = "actor_moved";
static const std::string kActorCreatedEventType = "actor_created";

namespace challenge
{
	class ActorEventData : public EventData
	{
	public:
		IActor *actor;
		glm::vec3 position;
		Model *model;


		ActorEventData(int timestamp) : EventData(timestamp) {}
		virtual std::string GetEventType() = 0;
	
	};

	class ActorAddedEventData: public ActorEventData
	{
	public:
		ActorAddedEventData(int timestamp) : ActorEventData(timestamp) {}
		virtual std::string GetEventType() { return kActorAddedEventType; }
	};

	class ActorMovedEventData: public ActorEventData
	{
	public:
		ActorMovedEventData(int timestamp) : ActorEventData(timestamp) {}
		virtual std::string GetEventType() { return kActorMovedEventType; }
	};

	class ActorCreatedEventData: public ActorEventData
	{
	public:
		ActorCreatedEventData(int timestamp) : ActorEventData(timestamp) {}
		virtual std::string GetEventType() { return kActorCreatedEventType; }
	};
};
