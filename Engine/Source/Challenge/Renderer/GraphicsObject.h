#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class IGraphicsDevice;

	class GraphicsObject
	{
	public:
		GraphicsObject(IGraphicsDevice *device) :
			mDevice(device)
		{
		}

		virtual ~GraphicsObject() = 0 {}

	protected:
		IGraphicsDevice * GetDevice() { return mDevice; }

	private:
		IGraphicsDevice *mDevice;
	};
};