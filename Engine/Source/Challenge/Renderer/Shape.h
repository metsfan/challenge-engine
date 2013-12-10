#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Material.h>

namespace challenge
{
	class Shape
	{
	public:
		Shape(IGraphicsDevice *device, std::string type) :
			mType(type),
			mDevice(device) {}
		virtual ~Shape() {}

		const std::string& GetString() const { return mType; }

		virtual void Draw(IGraphicsDevice *device, RenderState &state) = 0;

	protected:
		IGraphicsDevice* GetDevice() { return mDevice; }

	private:
		std::string mType;
		IGraphicsDevice *mDevice;
	};
};