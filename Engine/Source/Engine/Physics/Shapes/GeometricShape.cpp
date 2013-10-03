#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include <Engine/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	GeometricShape::GeometricShape() :
		mDebugShape(NULL)
	{
	}

	GeometricShape::GeometricShape(GeometricShape *other) :
		mPosition(other->mPosition),
		mBoundingBox(other->mBoundingBox),
		mDebugShape(NULL)
	{
	}

	void GeometricShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if(!mDebugShape) {
			mDebugShape = new MeshShape(device, "DebugLines");
			
		}

		this->CreateDebugShape(mDebugShape);
		mDebugShape->Draw(device, state);
	}
};

