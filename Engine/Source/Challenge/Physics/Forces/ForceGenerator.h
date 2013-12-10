#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/RigidBody.h>
 
namespace challenge
{
	class IForceGenerator
	{
	public:
		virtual void UpdateForce(RigidBody *body, real duration) = 0;
	};
};