#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape.h>
#include <Challenge/Util/Image.h>

namespace challenge
{
	struct SpriteVertex
	{
		float position[2];
	};

	class SpriteShape : public Shape
	{
	public:
		SpriteShape(IGraphicsDevice *device, const std::string &effect, ITexture *texture = NULL);
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

		void SetTextureFrame(real x, real y, real width, real height)
		{
			mTexFrame.x = x;
			mTexFrame.y = y;
			mTexFrame.z = width;
			mTexFrame.w = height;
		}

		void SetTextureFrame(const Frame &frame)
		{
			this->SetTextureFrame(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
		}

		void SetBorderColor(const Color &color)
		{
			mBorderColor = glm::vec4(color.red / 255.0f, color.green / 255.0f,
				color.blue / 255.0f, color.alpha / 255.0f);
		}

		void SetBorderWidth(float width)
		{
			mBorderWidth = width;
		}

		void Draw(IGraphicsDevice *device, RenderState &state); 

	protected:
		ITexture * GetTexture() { return mBackgroundImage; }
		void SetTexture(ITexture *texture) 
		{
			mBackgroundImage = texture; 
			mHasBackgroundImage = true;
		}

	private:
		glm::vec4 mBackgroundColor;
		ITexture *mBackgroundImage;
		bool mHasBackgroundImage;
		glm::vec4 mFrame;
		glm::vec4 mTexFrame;
		float mBorderWidth;
		glm::vec4 mBorderColor;
	};

};