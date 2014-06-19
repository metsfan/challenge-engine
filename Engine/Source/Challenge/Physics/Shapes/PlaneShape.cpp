#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
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
			BoxShape *aabb = static_cast<BoxShape *>(other);
			//intersects = IntersectionTests::AABBIntersectsPlane(aabb, this);
			break;
		}

		return intersects;
	}

	void PlaneShape::UpdateShape()
	{
		if (mCollisionShape) {
			delete mCollisionShape;
		}

		mCollisionShape = new btStaticPlaneShape(ToBullet(mNormal), mComponents.w);
	}
};



