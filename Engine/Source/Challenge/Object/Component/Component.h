#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class IComponent
	{
	public:
		virtual std::string GetType() = 0;

		virtual void Update(int deltaMillis) = 0;
	};

	class IRenderableComponent : public IComponent
	{
	public:
		virtual void Render(IGraphicsDevice *device, RenderState &state) = 0;
	};
};