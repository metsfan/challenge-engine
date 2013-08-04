#include <Engine/Challenge.h>

namespace challenge
{
	template <typename Renderer>
	PhongTechnique<Renderer>::PhongTechnique()
	{
		this->AddPass(new PhongPass<Renderer>());
	}

	template <typename Renderer>
	PhongTechnique<Renderer>::~PhongTechnique()
	{
	}
};