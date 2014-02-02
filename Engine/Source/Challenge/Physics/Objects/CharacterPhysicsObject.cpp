#include <Challenge/Challenge.h>
#include <Challenge/Physics/Objects/CharacterPhysicsObject.h>

namespace challenge
{
	void CharacterPhysicsObject::ResolveCollision(const CollisionData &collision)
	{
		PhysicsObject::ResolveCollision(collision);

		this->SetVelocity(glm::vec3(0));
	
		glm::vec3 origin = this->GetPosition() + glm::vec3(0, this->GetShape()->GetBoundingBox().GetHeight() * 0.5, 0);
		Ray castRay(origin, glm::vec3(0, -1, 0));
		float t;

		
		if (collision.other->GetPosition().x != 0) {
			int x = 0;
		}
		bool intersects = collision.other->GetShape()->RayIntersects(castRay, t);
		
		if (intersects) {
			

			glm::vec3 rayPos = castRay.ValueAt(t);
			glm::vec3 position = this->GetPosition();
			position.y = rayPos.y + this->GetShape()->GetBoundingBox().GetHeight() * 0.5;
			this->SetPosition(position);
		}
		
	}

	bool CharacterPhysicsObject::CollidesWith(PhysicsObject *other, CollisionData *collision)
	{
		// Cast a ray straight down the y axis into the other object
		return PhysicsObject::CollidesWith(other, collision);
	}
}