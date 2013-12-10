#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Technique.h>

namespace challenge
{
	template <typename Renderer>
	class BasicModelTechnique : public Technique 
	{
	public:
		BasicModelTechnique<Renderer>::BasicModelTechnique()
		{
			this->AddPass(new BasicModelPass<Renderer>());
		}

		~BasicModelTechnique()
		{
		}
	};
};