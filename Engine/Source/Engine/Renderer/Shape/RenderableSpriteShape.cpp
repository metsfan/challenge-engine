#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape/RenderableSpriteShape.h>

namespace challenge
{
	RenderableSpriteShape::RenderableSpriteShape(IGraphicsDevice *device, RENDER_TARGET_DESC desc) :
		SpriteShape(device),
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