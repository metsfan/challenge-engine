#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Material.h>

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