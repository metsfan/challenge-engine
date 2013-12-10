#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class IVertexBuffer
	{
	public:
		virtual void SetData(const void *buffer, int size) = 0;
		virtual void UpdateData(const void *buffer, int size, int offset) = 0;
		virtual void Activate(int offset) = 0;
		virtual void Activate() = 0;
	};

	class BaseVertexBuffer : public IVertexBuffer
	{
	};

	template <typename Renderer>
	class VertexBuffer : public BaseVertexBuffer {};
};