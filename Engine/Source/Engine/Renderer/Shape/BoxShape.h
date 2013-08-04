#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape.h>
#include <Engine/Renderer/VertexBuffer.h>
#include <Engine/Renderer/Material.h>
#include <Engine/Renderer/GraphicsDevice.h>

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