#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Technique.h>
#include <Engine/Renderer/RenderState.h>

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