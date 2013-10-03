#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape.h>

namespace challenge
{
	class IVertexBuffer;
	class Effect;

	class MeshShape : public Shape
	{
	public:
		MeshShape(IGraphicsDevice *device, const std::string &effect);
		~MeshShape();

		void SetData(const void *data, size_t size, int numVerts, PrimitiveType primType);

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		IVertexBuffer *mBuffer;
		Effect *mEffect;
		PrimitiveType mPrimType;
		int mNumVerts;
	};
};