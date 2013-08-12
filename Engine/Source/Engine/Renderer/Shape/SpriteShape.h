#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape.h>
#include <Engine/Util/Image.h>

namespace challenge
{
	struct SpriteVertex
	{
		float position[2];
	};

	class SpriteShape : public Shape
	{
	public:
		SpriteShape(IGraphicsDevice *device, ITexture *texture = NULL);
		~SpriteShape();

		void SetBackgroundColor(const glm::vec4 &color);
		void SetBackgroundImage(Image *backgroundImage);
		void SetSize(real width, real height)
		{
			mFrame.z = width;
			mFrame.w = height;
		}

		void SetPosition(real x, real y)
		{
			mFrame.x = x;
			mFrame.y = y;
		}

		void SetFrame(real x, real y, real width, real height)
		{
			mFrame.x = x;
			mFrame.y = y;
			mFrame.z = width;
			mFrame.w = height;
		}

		void SetFrame(const Frame &frame)
		{
			this->SetFrame(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
		}

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		glm::vec4 mBackgroundColor;
		ITexture *mBackgroundImage;
		bool mHasBackgroundImage;
		glm::vec4 mFrame;
	};

};