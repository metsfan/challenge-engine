#include <Challenge/Challenge.h>
#include "GravityForceGenerator.h"
using namespace challenge;

GravityForceGenerator::GravityForceGenerator(glm::vec3 gravity) :
	mGravity(gravity)
{
}

void GravityForceGenerator::ApplyForce(PhysicsObject *object, real duration)
{
	if (object->HasInfiniteMass()) {
		return;
	}

	object->ApplyForce(mGravity);
}