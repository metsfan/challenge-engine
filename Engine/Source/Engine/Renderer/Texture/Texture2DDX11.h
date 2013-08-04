#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>
#include <Engine/Renderer/Texture/TextureDX11.h>

namespace challenge
{
	template<>
	class Texture2D<RendererTypeDX11> : public TextureDX11
	{
	public:
		Texture2D(GraphicsDeviceDX11 *device, TEXTURE_DESC &desc);
		virtual ~Texture2D();

	private:
		ID3D11Texture2D *mDXTexture;
		D3D11_TEXTURE2D_DESC mTextureParams;

		bool LoadTextureData(std::vector<const BYTE *> &buffers);
	};

	typedef Texture2D<RendererTypeDX11> Texture2DDX11;
};