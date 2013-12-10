#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Attribute.h>
#include <Challenge/Renderer/Texture.h>

namespace challenge
{
	class TextureAttribute
	{
	public:
		TextureAttribute() :
			mTexture(NULL)
		{
		}

		~TextureAttribute()
		{
		}

		void SetTexture(ITexture *texture) { mTexture = texture; }
		ITexture* GetTexture() { return mTexture; }

	private:
		ITexture *mTexture;
	};
};