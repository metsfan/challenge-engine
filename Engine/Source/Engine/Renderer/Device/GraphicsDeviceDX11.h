#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/GraphicsDevice.h>

namespace challenge
{
	static const D3D11_PRIMITIVE_TOPOLOGY kD3D11PrimitiveTypes[5] = {
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	};

	static const D3D11_BLEND kD3D11BlendParams[19] = {
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ONE,
		D3D11_BLEND_SRC_COLOR,
		D3D11_BLEND_INV_SRC_COLOR,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_DEST_ALPHA,
		D3D11_BLEND_INV_DEST_ALPHA,
		D3D11_BLEND_DEST_COLOR,
		D3D11_BLEND_INV_DEST_COLOR,
		D3D11_BLEND_SRC_ALPHA_SAT,
		D3D11_BLEND_BLEND_FACTOR,
		D3D11_BLEND_INV_BLEND_FACTOR,
		D3D11_BLEND_SRC1_COLOR,
		D3D11_BLEND_INV_SRC1_COLOR,
		D3D11_BLEND_SRC1_ALPHA,
		D3D11_BLEND_INV_SRC1_ALPHA
	};

	static const D3D11_COMPARISON_FUNC kD3D11DepthFuncs[8] = {
		D3D11_COMPARISON_ALWAYS,
		D3D11_COMPARISON_NEVER,
		D3D11_COMPARISON_LESS,
		D3D11_COMPARISON_LESS_EQUAL,
		D3D11_COMPARISON_GREATER,
		D3D11_COMPARISON_GREATER_EQUAL,
		D3D11_COMPARISON_EQUAL,    
		D3D11_COMPARISON_NOT_EQUAL
	};

	template<>
	class GraphicsDevice<RendererTypeDX11> : public BaseGraphicsDevice
	{
	public:
		GraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, IWindow *window);
		~GraphicsDevice();

		ID3D11Device* GetD3D11Device() { return mDevice; }
		ID3D11DeviceContext* GetD3D11DeviceContext() { return mContext; }

		void SetWindowHandle(HWND window) { mWinHandle = window; }

		void SetBlendingFunction(BlendParam source, BlendParam destination);
		void SetDepthFunction(DepthFunc function);

		IShader* CreateShader(std::string filename, ShaderType type);
		IShaderProgram* CreateShaderProgram();
		IVertexBuffer* CreateVertexBuffer(VERTEX_BUFFER_DESC desc);
		ITexture* CreateTexture2D(TEXTURE_DESC &desc);
		ITexture* CreateTextureCube(TEXTURE_DESC &desc);

		void PreRender();
		void PostRender();

		void Draw(PrimitiveType type, int count, int start);

	private:
		HWND mWinHandle;
		IDXGISwapChain *mSwapChain;
		ID3D11Device *mDevice;
		ID3D11DeviceContext *mContext;
		ID3D11RenderTargetView *mRenderTargetView;
		ID3D11DepthStencilView *mDepthStencilView;
		ID3D11DepthStencilState *mDepthStencilState;
		ID3D11BlendState *mBlendState;
		D3D_FEATURE_LEVEL mFeatureLevel;

		D3D11_BLEND_DESC mBlendDesc;
		D3D11_DEPTH_STENCIL_DESC mDepthStencilDesc;

		void SetAlphaBlending(bool state);
		void SetDepthTest(bool state);
	};

	typedef GraphicsDevice<RendererTypeDX11> GraphicsDeviceDX11;
};