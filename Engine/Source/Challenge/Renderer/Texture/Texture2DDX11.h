#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>
#include <Challenge/Renderer/Texture/TextureDX11.h>

namespace challenge
{
	template<>
	class Texture2D<RendererTypeDX11> : public TextureDX11
	{
	public:
		Texture2D(GraphicsDeviceDX11 *device, TEXTURE_DESC &desc);
		virtual ~Texture2D();

		ID3D11Texture2D * GetDXTexture() { return mDXTexture; }

	private:
		ID3D11Texture2D *mDXTexture;
		D3D11_TEXTURE2D_DESC mTextureParams;

		bool LoadTextureData(std::vector<const BYTE *> &buffers);
	};

	typedef Texture2D<RendererTypeDX11> Texture2DDX11;
};