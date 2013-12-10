#pragma once

#include <Challenge/Core/Globals.h>
#include <Challenge/Renderer/Effect.h>
#include <Challenge/Renderer/Texture.h>

namespace challenge
{
	class SpriteEffect : public Effect
	{
	public:
		SpriteEffect();
		~SpriteEffect();

		void SetTexture(ITexture *texture) { mTexture = texture; }
		void UseTexture(bool useTexture) { mUseTexture = useTexture; }

		void SetColor(const glm::vec4 &color) { mColor = color; }

	private:
		ITexture *mTexture;
		bool mUseTexture;
		glm::vec4 mColor;


	};
};