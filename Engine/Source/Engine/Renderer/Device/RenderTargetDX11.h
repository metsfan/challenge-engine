#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/RenderTarget.h>
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	template<>
	class RenderTarget<RendererTypeDX11> : public BaseRenderTarget
	{
	public:
		RenderTarget(GraphicsDeviceDX11 *device, RENDER_TARGET_DESC desc = RENDER_TARGET_DESC());
		~RenderTarget();

		void Enabled();
		void Disable();
		void Clear();

	private:
		GraphicsDeviceDX11 *mDevice;

		ID3D11Texture2D *mDepthStencilBuffer;
		ID3D11RenderTargetView *mRenderTargetView;
		ID3D11DepthStencilView *mDepthStencilView;
		D3D11_VIEWPORT mViewport;

		ID3D11RenderTargetView *mPrevRenderTarget;
		ID3D11DepthStencilView *mPrevDepthStencil;
		D3D11_VIEWPORT mPrevViewport;
	};

	typedef RenderTarget<RendererTypeDX11> RenderTargetDX11;
};