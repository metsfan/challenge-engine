#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class IRenderTarget
	{
	public:
		virtual void Enabled() = 0;
		virtual void Disable() = 0;
		virtual void Clear() = 0;

		virtual ITexture * GetColorBuffer() = 0;
	};

	struct RENDER_TARGET_DESC
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		bool ColorBufferEnabled = true;
		ITexture *ColorTexture = NULL;
		bool DepthBufferEnabled = true;
		DepthStencilFormat DepthFormat = DepthStencilFormatNone;
	};

	class BaseRenderTarget : public IRenderTarget
	{
	public:
		BaseRenderTarget(RENDER_TARGET_DESC desc = RENDER_TARGET_DESC()) :
			mDesc(desc)
		{
		}

		virtual ~BaseRenderTarget()
		{
		}

		ITexture * GetColorBuffer() { return mDesc.ColorTexture; }

	protected:
		const RENDER_TARGET_DESC & GetDesc() { return mDesc; }

	private:
		RENDER_TARGET_DESC mDesc;

	};

	template <typename Renderer>
	class RenderTarget : public BaseRenderTarget
	{
	};
};