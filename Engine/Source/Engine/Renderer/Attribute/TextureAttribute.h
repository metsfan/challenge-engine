#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Attribute.h>
#include <Engine/Renderer/Texture.h>

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