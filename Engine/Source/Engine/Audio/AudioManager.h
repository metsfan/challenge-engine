#pragma once

#include <Engine/Challenge.h>
#include <FMOD/fmod.hpp>

namespace challenge
{
	class AudioManager
	{
		friend class Sound;
		friend class AudioListener;
		friend class SoundGroup;

	public: 
		AudioManager();
		~AudioManager();

		bool Initialize();
		
		AudioListener* GetListener() { return mListener; }

	private:
		FMOD::System *mAudioSystem;
		AudioListener *mListener;

		FMOD::System* GetAudioSystem() { return mAudioSystem; }
	};
};