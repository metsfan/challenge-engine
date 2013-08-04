#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include "PlaneShape.h"
using namespace challenge;

PlaneShape::PlaneShape(glm::vec4 components) :
	mComponents(components)
{
	mNormal = glm::vec3(components);
	mDistance = components.w;
}

bool PlaneShape::Intersects(IPhysicsShape *other, CollisionData *collision)
{
	PhysicsShapeType otherType = other->GetType();
	bool intersects = false;

	switch(otherType) {
	case kShapeTypeAABB:
		AABBShape *aabb = static_cast<AABBShape *>(other);
		intersects = IntersectionTests::AABBIntersectsPlane(aabb, this);
		break;
	}

	return intersects;
}


