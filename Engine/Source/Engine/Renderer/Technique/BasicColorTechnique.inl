#include <Engine/Challenge.h>
#include <Engine/Renderer/Pass/ModelAnimationPass.h>

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