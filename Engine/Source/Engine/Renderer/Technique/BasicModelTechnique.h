#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Technique.h>

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