#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/CharacterPhysicsObject.h>

namespace challenge
{
	void CharacterPhysicsObject::ResolveCollision(const CollisionData &collision)
	{
		PhysicsObject::ResolveCollision(collision);

		this->SetVelocity(glm::vec3(0));
	}
}