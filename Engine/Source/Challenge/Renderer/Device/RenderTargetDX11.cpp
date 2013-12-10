#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Device/RenderTargetDX11.h>
#include <Challenge/Renderer/Texture/Texture2DDX11.h>

namespace challenge
{
	RenderTargetDX11::RenderTarget(GraphicsDeviceDX11 *device, RENDER_TARGET_DESC desc) :
		BaseRenderTarget(desc),
		mDevice(device),
		mRenderTargetView(NULL),
		mDepthStencilView(NULL),
		mDepthStencilBuffer(NULL)
	{
		ID3D11Device *dxDevice = device->GetD3D11Device();
		ID3D11DeviceContext *dxContext = device->GetD3D11DeviceContext();
		HRESULT hr;

		if (desc.ColorTexture != NULL) {
			Texture2DDX11 *dxTexture = dynamic_cast<Texture2DDX11 *>(desc.ColorTexture);
			ID3D11Texture2D *texHandle = dxTexture->GetDXTexture();

			hr = dxDevice->CreateRenderTargetView(texHandle, NULL, &mRenderTargetView);
			if (hr != S_OK) {
				throw "Render target failed to initialize.";
			}
		}

		if (desc.DepthFormat != DepthStencilFormatNone) {
			D3D11_TEXTURE2D_DESC depthStencilTexDesc;
			depthStencilTexDesc.Width = desc.Width;
			depthStencilTexDesc.Height = desc.Height;
			depthStencilTexDesc.MipLevels = 1;
			depthStencilTexDesc.ArraySize = 1;
			depthStencilTexDesc.Format = DX11DepthStencilFormats[desc.DepthFormat];
			depthStencilTexDesc.SampleDesc.Count = 1;
			depthStencilTexDesc.SampleDesc.Quality = 0;
			depthStencilTexDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilTexDesc.CPUAccessFlags = 0;
			depthStencilTexDesc.MiscFlags = 0;

			ID3D11Texture2D *mDepthStencilBuffer;

			hr = dxDevice->CreateTexture2D(&depthStencilTexDesc, NULL, &mDepthStencilBuffer);
			if (FAILED(hr)) {
				throw "Failed to initialize render target!";
			}

			hr = dxDevice->CreateDepthStencilView(mDepthStencilBuffer, NULL, &mDepthStencilView);
			if (FAILED(hr)) {
				throw "Failed to initialize render target!";
			}
		}

		mViewport.Width = desc.Width;
		mViewport.Height = desc.Height;
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;
		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
	}

	RenderTargetDX11::~RenderTarget()
	{
		if (mRenderTargetView) {
			mRenderTargetView->Release();
		}

		if (mDepthStencilBuffer) {
			mDepthStencilBuffer->Release();
		}

		if (mDepthStencilView) {
			mDepthStencilView->Release();
		}
	}

	void RenderTargetDX11::Enabled()
	{
		ID3D11DeviceContext *dxContext = mDevice->GetD3D11DeviceContext();

		dxContext->OMGetRenderTargets(1, &mPrevRenderTarget, &mPrevDepthStencil);

		UINT mNumVps = 1;
		dxContext->RSGetViewports(&mNumVps, &mPrevViewport);

		dxContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
		dxContext->RSSetViewports(1, &mViewport);
	}

	void RenderTargetDX11::Disable()
	{
		ID3D11DeviceContext *dxContext = mDevice->GetD3D11DeviceContext();
		dxContext->OMSetRenderTargets(1, &mPrevRenderTarget, mPrevDepthStencil);
		dxContext->RSSetViewports(1, &mPrevViewport);
	}

	void RenderTargetDX11::Clear()
	{
		ID3D11DeviceContext *dxContext = mDevice->GetD3D11DeviceContext();

		if (mRenderTargetView) {
			FLOAT clearColor [] = { 0, 0, 0, 0 };
			dxContext->ClearRenderTargetView(mRenderTargetView, clearColor);
		}

		if (mDepthStencilView) {
			dxContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
	}
}