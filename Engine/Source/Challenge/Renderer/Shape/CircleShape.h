#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/MeshShape.h>

namespace challenge
{
	class CircleShape : public Shape
	{
	public:
		CircleShape(IGraphicsDevice *device);
		~CircleShape();

		void SetRadius(float radius)
		{
			mRadius.x = radius;
			mRadius.y = radius;
		}

		void SetXRadius(float radius)
		{
			mRadius.x = radius;
		}

		void SetYRadius(float radius)
		{
			mRadius.y = radius;
		}

		void SetColor(const Color &color)
		{
			mColor.r = color.red / 255.0f;
			mColor.g = color.green / 255.0f;
			mColor.b = color.blue / 255.0f;
			mColor.a = color.alpha / 255.0f;
		}

		void SetPosition(const glm::vec3 &position)
		{
			mPosition = position;
		}

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		glm::vec2 mRadius;
		glm::vec4 mColor;
		glm::vec3 mPosition;

		static MeshShape *sMesh;
	};
};