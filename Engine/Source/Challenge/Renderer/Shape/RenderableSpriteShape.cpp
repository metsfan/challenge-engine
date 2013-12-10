#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/RenderableSpriteShape.h>

namespace challenge
{
	RenderableSpriteShape::RenderableSpriteShape(IGraphicsDevice *device, RENDER_TARGET_DESC desc) :
		SpriteShape(device, "sprite"),
		mRenderTarget(device->CreateRenderTarget(desc))
	{
	}

	RenderableSpriteShape::~RenderableSpriteShape()
	{
		delete mRenderTarget;
	}

	void RenderableSpriteShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		this->SetTexture(mRenderTarget->GetColorBuffer());

		SpriteShape::Draw(device, state);
	}
}