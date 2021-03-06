#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/SpriteShape.h>
#include <Challenge/Renderer/RenderTarget.h>

namespace challenge
{
	class RenderableSpriteShape : public SpriteShape
	{
	public:
		RenderableSpriteShape(IGraphicsDevice *device, RENDER_TARGET_DESC desc = RENDER_TARGET_DESC());
		~RenderableSpriteShape();

		void Draw(IGraphicsDevice *device, RenderState &state);

		void EnableRenderTarget() { mRenderTarget->Enabled(); }
		void DisableRenderTarget() { mRenderTarget->Disable(); }
		void ClearRenderTarget() { mRenderTarget->Clear(); }

	private:
		IRenderTarget *mRenderTarget;
	};
};