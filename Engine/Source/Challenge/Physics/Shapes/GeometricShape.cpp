#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>
#include <Challenge/Model/Model.h>

#include <BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h>

namespace challenge
{
	GeometricShape::GeometricShape() :
		mDebugShape(NULL),
		mCollisionShape(NULL)
	{
	}

	GeometricShape::GeometricShape(GeometricShape *other) :
		mPosition(other->mPosition),
		mBoundingBox(other->mBoundingBox),
		mDebugShape(NULL)
	{
	}

	GeometricShape::~GeometricShape()
	{
	}

	bool GeometricShape::Intersects(const IGeometricShape *other, CollisionData *collision) const
	{
		return false;
	}

	/*void GeometricShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		this->CreateDebugShape(NULL);
		mDebugShape->Render(device, state);
	}*/
};

