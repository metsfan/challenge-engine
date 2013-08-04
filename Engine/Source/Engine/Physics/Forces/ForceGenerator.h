#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Objects/RigidBody.h>
 
namespace challenge
{
	class IForceGenerator
	{
	public:
		virtual void UpdateForce(RigidBody *body, real duration) = 0;
	};
};