#pragma once

#include <Engine/Challenge.h>
#include <FMOD/fmod.hpp>

namespace challenge
{
	class AudioListener
	{
	public:
		AudioListener();
		~AudioListener();

		void SetPosition(glm::vec3 position);
		void SetOrientation(glm::vec3 orientation);
		void SetVelocity(glm::vec3 velocity);

		void Update();

	private:
		FMOD_VECTOR mPosition;
		FMOD_VECTOR mOrientation;
		FMOD_VECTOR mVelocity;
		FMOD_VECTOR mUp;
		FMOD_VECTOR mForward;
	};
};