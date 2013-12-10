#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Lights/LightSource.h>

namespace challenge
{
	class PointLightSource : public LightSource
	{
	public:
		PointLightSource() :
			LightSource(LightSourcePoint)
		{
		}

		~PointLightSource()
		{
		}

		void SetPosition(glm::vec3 position) { mPosition = position; }
		const glm::vec3& GetPosition() const { return mPosition; }

	private:
		glm::vec3 mPosition;
		
	};
};