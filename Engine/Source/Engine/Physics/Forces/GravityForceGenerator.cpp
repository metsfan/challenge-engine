#include <Engine/Challenge.h>
#include "GravityForceGenerator.h"
using namespace challenge;

GravityForceGenerator::GravityForceGenerator(glm::vec3 gravity) :
	mGravity(gravity)
{
}

void GravityForceGenerator::UpdateForce(RigidBody *body, real duration)
{
	if(body->HasInfiniteMass()) { return; }

	body->AddForce(mGravity * body->mMass);
}