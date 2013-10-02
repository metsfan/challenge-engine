#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include "PlaneShape.h"

namespace challenge
{
	PlaneShape::PlaneShape(glm::vec4 components) :
	mComponents(components)
	{
		mNormal = glm::vec3(components);
	}

	bool PlaneShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		GeometricShapeType otherType = other->GetType();
		bool intersects = false;

		switch(otherType) {
		case kShapeTypeAABB:
			AABBShape *aabb = static_cast<AABBShape *>(other);
			intersects = IntersectionTests::AABBIntersectsPlane(aabb, this);
			break;
		}

		return intersects;
	}
};



