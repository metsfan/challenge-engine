#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	struct BasicVertex
	{
		float position[3];
		float color[4];
		float texCoord[2];
	};

	enum MultisampleLevel
	{
		MultisampleLevelNone,
		MultisampleLevel4X
	};

	struct GRAPHICS_DEVICE_DESC
	{
		MultisampleLevel MultiSampling;
	};

	enum VertexBufferCPUAccessFlags
	{
		VertexBufferCPURead = 0x0001,
		VertexBufferCPUWrite = 0x0002
	};

	enum VertexBufferUsage
	{
		VertexBufferUsageDefault,
		VertexBufferUsageStatic,
		VertexBufferUsageDynamic
	};

	struct VERTEX_BUFFER_DESC
	{
		int Stride; // Distance between vertices in this buffer
		uint32_t CPUAccess; // CPU Access, can be any combination or'ed together, or 0
		VertexBufferUsage Usage; // How the buffer is going to be used
	};

	enum PrimitiveType
	{
		PrimitiveTypeTriangleList,
		PrimitiveTypeTriangleStrip,
		PrimitiveTypeLineList,
		PrimitiveTypeLineStrip,
		PrimitiveTypePointList
	};
};
