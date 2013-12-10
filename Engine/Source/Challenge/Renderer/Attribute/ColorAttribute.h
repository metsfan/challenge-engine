#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Attribute.h>

namespace challenge
{
	class ColorAttribute
	{
	public:
		ColorAttribute()
		{
		}

		~ColorAttribute()
		{
		}

		const glm::vec4& GetColor() const { return mColor; }
		void SetColor(int r, int g, int b, int a)
		{
			mColor.r = (float)r / 255.0f;
			mColor.g = (float)g / 255.0f;
			mColor.b = (float)b / 255.0f;
			mColor.a = (float)a / 255.0f;	
		}

		void SetColor(float r, float g, float b, float a)
		{
			mColor.r = r;
			mColor.g = g;
			mColor.b = b;
			mColor.a = a;
		}

	private:
		glm::vec4 mColor;
	};
};