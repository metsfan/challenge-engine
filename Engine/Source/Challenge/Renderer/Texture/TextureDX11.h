#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	static const DXGI_FORMAT DX11TextureFormats[] = {
		DXGI_FORMAT_R32_UINT,		//TextureFormatInt32
		DXGI_FORMAT_R32_FLOAT,		//TextureFormatFloat32
		DXGI_FORMAT_R8G8B8A8_UNORM,	//TextureFormatRGBA
		DXGI_FORMAT_B8G8R8A8_UNORM, //TextureFormatBGRA
		DXGI_FORMAT_A8_UNORM		//TextureFormatAlpha
	};

	static const DXGI_FORMAT DX11DepthStencilFormats [] = {
		DXGI_FORMAT_UNKNOWN,			// DepthStencilFormatNone
		DXGI_FORMAT_D24_UNORM_S8_UINT,  // DepthStencilFormatD24S8
		DXGI_FORMAT_D16_UNORM,			// DepthStencilFormatD16
		DXGI_FORMAT_D32_FLOAT			// DepthStencilFormatD32
	};

	template<>
	class Texture<RendererTypeDX11> : public BaseTexture
	{
	public:
		Texture(GraphicsDeviceDX11 *device, TEXTURE_DESC &desc);
		virtual ~Texture();


		ID3D11ShaderResourceView * GetTextureResource() { return mDXResourceView; }

	protected:
		void SetTextureResource(ID3D11ShaderResourceView *resource)
		{
			mDXResourceView = resource;
		}

		GraphicsDeviceDX11* GetDevice() { return mDevice; }
		TEXTURE_DESC& GetDesc() { return mDesc; }

	private:
		GraphicsDeviceDX11 *mDevice;
		ID3D11ShaderResourceView *mDXResourceView;
		TEXTURE_DESC mDesc;

		virtual bool LoadTextureData(std::vector<const BYTE *> &buffers) = 0;
	};

	typedef Texture<RendererTypeDX11> TextureDX11;
};

