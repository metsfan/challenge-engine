#include <Challenge/Challenge.h>
#include "CollisionDetector.h"

namespace challenge
{
	CollisionDetector::CollisionDetector()
	{
	}

	void CollisionDetector::ResolveCollision(std::vector<PhysicsObject *> objects)
	{
		while (objects.size()) {
			PhysicsObject *obj1 = objects.back();

			for (PhysicsObject *obj2 : objects) {
				if (obj1 != obj2) {
					CollisionData collision;
					if (obj1->CollidesWith(obj2, &collision)) {
						if (!obj1->HasInfiniteMass()) {
							obj1->ResolveCollision(collision);
						}

						if (!obj2->HasInfiniteMass()) {
							obj2->ResolveCollision(collision);
						}
					}
				}
			}

			objects.pop_back();
		}
	}
}


