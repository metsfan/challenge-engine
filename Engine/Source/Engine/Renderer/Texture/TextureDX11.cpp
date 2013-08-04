#include <Engine/Challenge.h>
#include <Engine/Renderer/Texture/TextureCubeDX11.h>

namespace challenge
{
	Texture<RendererTypeDX11>::Texture(GraphicsDevice<RendererTypeDX11> *device, TEXTURE_DESC &desc) :
		BaseTexture(),
		mDevice(device),
		mDXResourceView(NULL),
		mDesc(desc)
	{
	}

	Texture<RendererTypeDX11>::~Texture()
	{
	}
};