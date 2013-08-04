#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>
#include <Engine/Renderer/Texture/TextureDX11.h>

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