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

			/*D3D11_DEPTH_STENCIL_DESC dsDesc;
			dsDesc.DepthEnable = true;
			dsDesc.DepthFunc = D3D11_COMPARISON_GREATER;
			mDevice->CreateDepthStencilState(&dsDesc, &mDepthStencilState);*/

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

			D3D11_RASTERIZER_DESC rsDesc;
			ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
			rsDesc.FillMode = D3D11_FILL_SOLID;
			rsDesc.CullMode = D3D11_CULL_NONE;
			rsDesc.FrontCounterClockwise = true;

			ID3D11RasterizerState *rsState;

			mDevice->CreateRasterizerState(&rsDesc, &rsState);
			mContext->RSSetState(rsState);
		}
	}

	GraphicsDevice<RendererTypeDX11>::~GraphicsDevice()
	{
		mSwapChain->Release();
		mDevice->Release();
		mRenderTargetView->Release();
		mDepthStencilView->Release();
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