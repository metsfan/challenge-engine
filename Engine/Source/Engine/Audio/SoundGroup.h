#pragma once

#include <Engine/Challenge.h>
#include <FMOD/fmod.hpp>

namespace challenge
{
	class Sound;
	typedef std::vector<Sound *> TSoundList;

	class SoundGroup
	{
	public: 
		SoundGroup(std::string name);
		~SoundGroup();

		void AddSound(Sound *sound);

		void Play();
		void Stop();
		void Pause();
		void Rewind();

		void SetVolume(float volume);
		void SetLooping(bool looping);

		void SetPosition(int index, glm::vec3 position);
		void SetVelocity(int index, glm::vec3 velocity);

	private:
		FMOD::ChannelGroup *mChannelGroup;
		FMOD::SoundGroup *mSoundGroup;
		TSoundList mSounds;
		std::string mName;
		
	};
};