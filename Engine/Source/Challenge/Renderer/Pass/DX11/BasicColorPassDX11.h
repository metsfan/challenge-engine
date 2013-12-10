#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Pass/BasicColorPass.h>

namespace challenge
{
	template<>
	class BasicColorPass<RendererTypeDX11> : public Pass
	{
	public:
		BasicColorPass();
		~BasicColorPass();

		void Apply(IGraphicsDevice *device, RenderState &state);
	};
};