#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Pass/BasicColorPass.h>

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