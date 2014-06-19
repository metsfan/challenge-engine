#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/CapsuleShape.h>

namespace challenge
{
	CapsuleShape::CapsuleShape(real radius, real height, CapsuleAxis axis) :
		mRadius(radius),
		mHeight(height),
		mAxis(mAxis)
	{
		this->UpdateShape();
	}

	CapsuleShape::~CapsuleShape()
	{
	}

	void CapsuleShape::UpdateShape()
	{
		if (mCollisionShape) {
			delete mCollisionShape;
		}

		switch (mAxis)
		{
		case CapsuleAxisX:
			mCollisionShape = new btCapsuleShapeX(mRadius, mHeight);
			break;

		case CapsuleAxisZ:
			mCollisionShape = new btCapsuleShapeZ(mRadius, mHeight);
			break;

		default:
			mCollisionShape = new btCapsuleShape(mRadius, mHeight);
		}
		
	}
}