#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/LineShape.h>

namespace challenge
{
	LineShape::LineShape(IGraphicsDevice *device) :
		Shape(device, "line"),
		mReloadPoints(false),
		mMesh(NULL),
		mColor(1, 0, 0, 1),
		mWidth(5)
	{
	}

	LineShape::~LineShape()
	{
	}

	void LineShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		if (mPoints.size() > 0) {
			if (!mMesh) {
				mMesh = new MeshShape(device, "Line");
			}

			if (mReloadPoints) {
				mMesh->SetData(&mPoints[0], sizeof(glm::vec3) * mPoints.size(), mPoints.size(), PrimitiveTypeLineStrip);
				mReloadPoints = false;
			}

			state.SetShaderData(device->GetContext()->GetGlobalIndex("WIDTH"), &mWidth);
			state.SetShaderData(device->GetContext()->GetGlobalIndex("COLOR"), &mColor);
			
			mMesh->Draw(device, state);
		}
	}
}