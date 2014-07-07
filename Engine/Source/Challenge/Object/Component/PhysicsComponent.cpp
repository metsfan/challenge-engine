#include <Challenge/Challenge.h>
#include <Challenge/Object/Component/PhysicsComponent.h>
#include <Challenge/Object/GameObject.h>

namespace challenge
{
	PhysicsComponent::PhysicsComponent(GameObject *owner, PhysicsObject *object) :
		BaseComponent(owner),
		mObject(object)
	{
		object->SetUserData(owner);
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}

	void PhysicsComponent::Update(int deltaMillis)
	{
		this->GetOwner()->MoveTo(mObject->GetPosition());
	}
}