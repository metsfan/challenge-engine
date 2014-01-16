#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Object/Component/Component.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>

namespace challenge
{
	class PhysicsComponent : public BaseComponent
	{
	public:
		PhysicsComponent(GameObject *owner, PhysicsObject *object);
		~PhysicsComponent();

		std::string GetType() { return "physics"; }

		PhysicsObject * GetPhysicsObject() { return mObject; }

		void Update(int deltaMillis);

		void UpdatePhysics();

	private:
		PhysicsObject *mObject;
	};
};