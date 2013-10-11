#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include <Engine/Physics/Shapes/GeometricShape.h>
#include <Engine/Model/Model.h>

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

	GeometricShape::~GeometricShape()
	{
	}

	/*void GeometricShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		this->CreateDebugShape(NULL);
		mDebugShape->Render(device, state);
	}*/
};

