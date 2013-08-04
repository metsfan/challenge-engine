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

	template<>
	class GraphicsDevice<RendererTypeDX11> : public BaseGraphicsDevice
	{
	public:
		GraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, IWindow *window);
		~GraphicsDevice();

		ID3D11Device* GetD3D11Device() { return mDevice; }
		ID3D11DeviceContext* GetD3D11DeviceContext() { return mContext; }

		void SetWindowHandle(HWND window) { mWinHandle = window; }

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
		D3D_FEATURE_LEVEL mFeatureLevel;
	};

	typedef GraphicsDevice<RendererTypeDX11> GraphicsDeviceDX11;
};