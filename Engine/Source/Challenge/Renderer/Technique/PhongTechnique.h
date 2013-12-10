#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Technique.h>
#include <Challenge/Renderer/Pass/PhongPass.h>

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