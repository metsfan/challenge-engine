#pragma once

#include <Engine/Core/Globals.h>
#include <Engine/Renderer/Effect.h>
#include <Engine/Renderer/Texture.h>

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