#pragma once

#include <Engine/Challenge.h>
#include <FMOD/fmod.hpp>

namespace challenge
{
	static const std::string kSoundDir = "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Media/Sounds/";

	class Sound
	{
		friend class SoundGroup;

	public:
		Sound(std::string filename, glm::vec3 position, bool loop);
		virtual ~Sound();

		void Play();
		void Stop();
		void Pause();
		void Rewind();

		void SetVolume(float volume);
		void SetLooping(bool looping);

		void SetPosition(glm::vec3 position);
		void SetVelocity(glm::vec3 velocity);

		void Update();

	protected:
		std::string mFilepath;
		FMOD_VECTOR mPosition;
		FMOD_VECTOR mVelocity;
		FMOD::Sound *mSound;
		FMOD::Channel *mChannel;
		float mVolume;
		bool mLooping;
	};
};