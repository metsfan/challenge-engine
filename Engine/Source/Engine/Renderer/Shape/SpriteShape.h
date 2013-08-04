#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape.h>
#include <Engine/Util/Image.h>

namespace challenge
{
	struct SpriteVertex
	{
		float position[2];
		float texCoord[2];
	};

	class SpriteShape : public Shape
	{
	public:
		SpriteShape(IGraphicsDevice *device);
		~SpriteShape();

		void SetBackgroundColor(const glm::vec4 &color);
		void SetBackgroundImage(Image *backgroundImage);

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		glm::vec4 mBackgroundColor;
		ITexture *mBackgroundImage;
	};

};