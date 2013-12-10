#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Technique.h>
#include <Challenge/Renderer/RenderState.h>

namespace challenge
{
	template <typename Renderer>
	class BasicColorTechnique : public Technique 
	{
	public:
		BasicColorTechnique();
		~BasicColorTechnique();
	};
};

#include "BasicColorTechnique.inl"