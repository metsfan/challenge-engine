#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape.h>
#include <Challenge/Renderer/VertexBuffer.h>
#include <Challenge/Renderer/Material.h>
#include <Challenge/Renderer/GraphicsDevice.h>

namespace challenge
{
	struct BoxVertex
	{
		float position[4];
		float normal[3];
	};

	class BoxShape : public Shape
	{
	public:
		BoxShape(IGraphicsDevice *device, int size);
		~BoxShape();

		virtual void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		int mSize;
		IVertexBuffer *mBuffer;
		Material *mMaterial;
		
	};
};