#include <Challenge/Challenge.h>
#include "CollisionDetector.h"

namespace challenge
{
	CollisionDetector::CollisionDetector()
	{
	}

	void CollisionDetector::ResolveCollision(std::vector<PhysicsObject *> objects)
	{
		for (PhysicsObject *obj1 : objects) {
			for (PhysicsObject *obj2 : objects) {
				if (obj1 != obj2) {
					// Skip this pass if both objects have infinite mass
					if (obj1->HasInfiniteMass() &&
						obj2->HasInfiniteMass()) {
						continue;
					}

					CollisionData collision;
					if (obj1->CollidesWith(obj2, &collision)) {
						if (!obj1->HasInfiniteMass()) {
							collision.other = obj2;
							obj1->ResolveCollision(collision);
						}

						if (!obj2->HasInfiniteMass()) {
							collision.other = obj1;
							obj2->ResolveCollision(collision);
						}
					}
				}
			}
		}
	}
}


