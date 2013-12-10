#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>
#include <Challenge/Renderer/Texture/TextureDX11.h>

namespace challenge
{
	template<>
	class TextureCube<RendererTypeDX11> : public TextureDX11
	{
	public:
		TextureCube(GraphicsDeviceDX11 *device, TEXTURE_DESC &desc);
		virtual ~TextureCube();

	private:
		ID3D11Texture2D *mDXTexture;
		D3D11_TEXTURE2D_DESC mTextureParams;

		bool LoadTextureData(std::vector<const BYTE *> &buffers);
	};

	typedef TextureCube<RendererTypeDX11> TextureCubeDX11;
};