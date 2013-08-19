#include <Engine/Challenge.h>
#include "GraphicsDeviceDX11.h"
#include <Engine/Renderer/Shader/DX11/ShaderDX11.h>
#include <Engine/Renderer/Shader/DX11/ShaderProgramDX11.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/Renderer/Texture/TextureCubeDX11.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>

namespace challenge
{
	GraphicsDevice<RendererTypeDX11>::GraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, IWindow *window) :
		BaseGraphicsDevice(graphicsDesc, window),
		mWinHandle(NULL),
		mDevice(NULL)
	{
		GraphicsContext<RendererTypeDX11> *context = new GraphicsContext<RendererTypeDX11>();
		this->SetGraphicsContext(static_cast<IGraphicsContext *>(context));

		window->AttachToDevice(this);

		if(mWinHandle) {
			const Size& size = window->GetSize();

			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory( &sd, sizeof( sd ) );

			sd.BufferDesc.Width = size.width;
			sd.BufferDesc.Height = size.height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;

			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;
			sd.OutputWindow = mWinHandle;
			sd.Windowed = TRUE;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = 0; 

			D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_10_1;

			HRESULT hr = S_OK;

			if( FAILED (hr = D3D11CreateDeviceAndSwapChain( NULL, 
							D3D_DRIVER_TYPE_HARDWARE,
							NULL, 
							D3D11_CREATE_DEVICE_DEBUG,
							&FeatureLevels, 
							1, 
							D3D11_SDK_VERSION, 
							&sd, 
							&mSwapChain, 
							&mDevice, 
							&mFeatureLevel,
							&mContext )))
			{
				throw "Failed to initialize DirectX!";
			}

			ID3D11Texture2D *backBuffer;

			hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBuffer);
			if( FAILED(hr)) {
				throw "Failed to initialize DirectX!";
			}

			mDevice->CreateRenderTargetView(backBuffer, NULL, &mRenderTargetView);
	
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			depthStencilDesc.Width = size.width;
			depthStencilDesc.Height = size.height;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;

			ID3D11Texture2D *depthStencilBuffer;

			hr = mDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
			if(FAILED(hr)) {
				throw "Failed to initialize DirectX!";
			}

			hr = mDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &mDepthStencilView);
			if(FAILED(hr)) {
				throw "Failed to initialize DirectX!";
			}

			ZeroMemory(&mDepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
			mDepthStencilDesc.DepthEnable = true;
			mDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			mDepthStencilDesc.StencilEnable = false;
			mDevice->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
			mContext->OMSetDepthStencilState(mDepthStencilState, 0);

			ZeroMemory(&mBlendDesc, sizeof(D3D11_BLEND_DESC));
			mBlendDesc.RenderTarget[0].BlendEnable = true;
			mBlendDesc.RenderTarget[0].SrcBlend = kD3D11BlendParams[BlendSrcAlpha];
			mBlendDesc.RenderTarget[0].SrcBlendAlpha = kD3D11BlendParams[BlendSrcAlpha];
			mBlendDesc.RenderTarget[0].DestBlend = kD3D11BlendParams[BlendOneMinusSrcAlpha];
			mBlendDesc.RenderTarget[0].DestBlendAlpha = kD3D11BlendParams[BlendOneMinusSrcAlpha];
			mBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			mBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			mBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

			mDevice->CreateBlendState(&mBlendDesc, &mBlendState);

			FLOAT blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			UINT sampleMask = 0xFFFFFFFF;
			mContext->OMSetBlendState(mBlendState, NULL, sampleMask);

			mContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
			backBuffer->Release();

			D3D11_VIEWPORT vp;
			vp.Width = size.width;
			vp.Height = size.height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			mContext->RSSetViewports(1, &vp);

			ZeroMemory(&mRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
			mRasterizerDesc.FillMode = D3D11_FILL_SOLID;
			mRasterizerDesc.CullMode = D3D11_CULL_NONE;
			mRasterizerDesc.FrontCounterClockwise = true;

			mDevice->CreateRasterizerState(&mRasterizerDesc, &mRasterizerState);
			mContext->RSSetState(mRasterizerState);
		}
	}

	GraphicsDevice<RendererTypeDX11>::~GraphicsDevice()
	{
		mSwapChain->Release();
		mDevice->Release();
		mRenderTargetView->Release();
		mDepthStencilView->Release();
	}

	void GraphicsDevice<RendererTypeDX11>::SetAlphaBlending(bool blending)
	{
		if(mBlendDesc.RenderTarget[0].BlendEnable != blending) {
			mBlendDesc.RenderTarget[0].BlendEnable = blending;

			mBlendState->Release();
			mDevice->CreateBlendState(&mBlendDesc, &mBlendState);
			UINT sampleMask = 0xFFFFFFFF;
			mContext->OMSetBlendState(mBlendState, NULL, sampleMask);
		}
	}

	void GraphicsDevice<RendererTypeDX11>::SetDepthTest(bool state)
	{
		if(mDepthStencilDesc.DepthEnable != state) {
			mDepthStencilDesc.DepthEnable = state;

			mDepthStencilState->Release();
			mDevice->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
			mContext->OMSetDepthStencilState(mDepthStencilState, 0);
		}
	}

	void GraphicsDevice<RendererTypeDX11>::SetScissorTest(bool state)
	{
		if(mRasterizerDesc.ScissorEnable != state) {
			mRasterizerDesc.ScissorEnable = state;

			mRasterizerState->Release();
			mDevice->CreateRasterizerState(&mRasterizerDesc, &mRasterizerState);
			mContext->RSSetState(mRasterizerState);
		}
	}

	void GraphicsDevice<RendererTypeDX11>::SetDepthFunction(DepthFunc function)
	{
		if(mDepthStencilDesc.DepthFunc != kD3D11DepthFuncs[function]) {
			mDepthStencilDesc.DepthFunc = kD3D11DepthFuncs[function];

			mDepthStencilState->Release();
			mDevice->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
			mContext->OMSetDepthStencilState(mDepthStencilState, 0);
		}
	}

	void GraphicsDevice<RendererTypeDX11>::SetBlendingFunction(BlendParam source, BlendParam destination)
	{
		if(mBlendDesc.RenderTarget[0].SrcBlend != kD3D11BlendParams[source] &&
			mBlendDesc.RenderTarget[0].DestBlend != kD3D11BlendParams[destination]) {

			mBlendDesc.RenderTarget[0].SrcBlend = kD3D11BlendParams[source];
			mBlendDesc.RenderTarget[0].SrcBlendAlpha = kD3D11BlendParams[source];
			mBlendDesc.RenderTarget[0].DestBlend = kD3D11BlendParams[destination];
			mBlendDesc.RenderTarget[0].DestBlendAlpha = kD3D11BlendParams[destination];

			mBlendState->Release();
			mDevice->CreateBlendState(&mBlendDesc, &mBlendState);
			mContext->OMSetBlendState(mBlendState, NULL, 0);
		}
	}

	void GraphicsDevice<RendererTypeDX11>::SetScissorRect(int x, int y, int width, int height)
	{
		mScissorRect.left = x;
		mScissorRect.right = x + width;
		mScissorRect.top = y;
		mScissorRect.bottom = y + height;
		mContext->RSSetScissorRects(1, &mScissorRect);
	}

	IShader* GraphicsDevice<RendererTypeDX11>::CreateShader(std::string filename, ShaderType type)
	{
		Shader<RendererTypeDX11> *shader = new Shader<RendererTypeDX11>(this, filename, type);
		return static_cast<IShader *>(shader);
	}

	IShaderProgram* GraphicsDevice<RendererTypeDX11>::CreateShaderProgram()
	{
		ShaderProgram<RendererTypeDX11> *shaderProgram = new ShaderProgram<RendererTypeDX11>(this);
		return static_cast<IShaderProgram *>(shaderProgram);
	}

	IVertexBuffer* GraphicsDevice<RendererTypeDX11>::CreateVertexBuffer(VERTEX_BUFFER_DESC desc)
	{
		return new VertexBuffer<RendererTypeDX11>(this, desc);
	}

	ITexture* GraphicsDevice<RendererTypeDX11>::CreateTexture2D(TEXTURE_DESC &desc)
	{
		return new Texture2D<RendererTypeDX11>(this, desc);
	}

	ITexture* GraphicsDevice<RendererTypeDX11>::CreateTextureCube(TEXTURE_DESC &desc)
	{
		return new TextureCube<RendererTypeDX11>(this, desc);
	}

	void GraphicsDevice<RendererTypeDX11>::PreRender()
	{
		float clearColor[4] = { 1.0, 1.0, 1.0, 1.0 };
		mContext->ClearRenderTargetView(mRenderTargetView, clearColor);
		mContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void GraphicsDevice<RendererTypeDX11>::PostRender()
	{
		mSwapChain->Present(0, 0);
	}

	void GraphicsDevice<RendererTypeDX11>::Draw(PrimitiveType type, int count, int start)
	{
		mContext->IASetPrimitiveTopology(kD3D11PrimitiveTypes[type]);
		mContext->Draw(count, start);
	}
};