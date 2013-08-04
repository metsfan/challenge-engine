#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Lights/LightSource.h>

namespace challenge
{
	class DirectionalLightSource : public LightSource
	{
	public:
		DirectionalLightSource() :
			LightSource(LightSourceDirectional)
		{
		}

		~DirectionalLightSource()
		{
		}

		void SetDirection(glm::vec3 direction) { mDirection = direction; }
		const glm::vec3& GetPosition() const { return mDirection; }

	private:
		glm::vec3 mDirection;
		
	};
};