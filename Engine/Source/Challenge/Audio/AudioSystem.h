#pragma once

#include <Challenge/Challenge.h>
#include <FMOD/fmod.hpp>

namespace challenge
{
	class AudioSystem
	{
		friend class Sound;
		friend class AudioListener;
		friend class SoundGroup;

	public: 
		static bool Initialize();
		
		static AudioListener * GetListener() { return mListener; }

	private:
		static FMOD::System *mAudioSystem;
		static AudioListener *mListener;

		static FMOD::System * GetFMODSystem() { return mAudioSystem; }
	};
};