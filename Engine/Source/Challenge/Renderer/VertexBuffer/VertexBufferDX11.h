#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/VertexBuffer.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	template<>
	class VertexBuffer<RendererTypeDX11> : public BaseVertexBuffer
	{
	public:
		VertexBuffer(GraphicsDevice<RendererTypeDX11> *device, VERTEX_BUFFER_DESC desc);
		VertexBuffer(GraphicsDevice<RendererTypeDX11> *device, void *buffer, int size, D3D11_USAGE usage, int stride);

		/* IVertexBuffer methods */
		void SetData(const void *buffer, int size, int stride = 0);
		void UpdateData(const void *buffer, int size, int offset);
		void Activate(int offset);
		void Activate();

	protected:
		GraphicsDevice<RendererTypeDX11> *mDevice;
		ID3D11Buffer *mBuffer;
		int mStride;
		VERTEX_BUFFER_DESC mDesc;
	};
};