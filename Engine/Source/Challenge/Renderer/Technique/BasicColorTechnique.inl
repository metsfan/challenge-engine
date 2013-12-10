#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Pass/ModelAnimationPass.h>

namespace challenge
{
	template <typename Renderer>
	BasicColorTechnique<Renderer>::BasicColorTechnique()
	{
		this->AddPass(new ModelAnimationPass<Renderer>());
	}

	template <typename Renderer>
	BasicColorTechnique<Renderer>::~BasicColorTechnique()
	{
	}
};