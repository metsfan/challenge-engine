#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/PhysicsObject.h>
 
namespace challenge
{
	class IForceGenerator
	{
	public:
		virtual void ApplyForce(PhysicsObject *object, real duration) = 0;
	};
};