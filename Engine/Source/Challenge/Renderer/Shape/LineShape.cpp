#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/LineShape.h>

namespace challenge
{
	LineShape::LineShape(IGraphicsDevice *device) :
		Shape(device, "line"),
		mReloadPoints(false)
	{
		mMesh = new MeshShape(device, "Line");
	}

	LineShape::~LineShape()
	{
		delete mMesh;
	}

	void LineShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		if (mPoints.size() > 0) {
			if (mReloadPoints) {
				mMesh->SetData(&mPoints[0], sizeof(glm::vec3) * mPoints.size(), mPoints.size(), PrimitiveTypeLineStrip);
				mReloadPoints = false;
			}

			ShaderDataFloat widthData(&mWidth, 1);
			state.SetShaderData("WIDTH", &widthData);

			ShaderDataVector4 colorData(&mColor, 1);
			state.SetShaderData("COLOR", &colorData);
			
			mMesh->Draw(device, state);
		}
	}
}