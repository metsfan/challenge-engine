#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Technique.h>
#include <Engine/Renderer/Pass/PhongPass.h>

namespace challenge
{
	template <typename Renderer>
	class PhongTechnique : public Technique 
	{
	public:
		PhongTechnique();
		~PhongTechnique();
	};
};

#include "PhongTechnique.inl"