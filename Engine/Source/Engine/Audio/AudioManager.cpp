#include <Engine/Challenge.h>
#include "AudioManager.h"
#include <Engine/Audio/AudioListener.h>
using namespace challenge;

AudioManager::AudioManager()
{
	mAudioSystem = NULL;
}

AudioManager::~AudioManager()
{
}

bool AudioManager::Initialize()
{
	FMOD_RESULT result;
	int numDrivers;
	FMOD::System *system;
	FMOD_CAPS caps;
	FMOD_SPEAKERMODE speakerMode;

	result = FMOD::System_Create(&system);
	if(result != FMOD_OK) {
		return false;
	}

	system->getNumDrivers(&numDrivers);
	if(numDrivers == 0) {
		system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
	} else {
		system->getDriverCaps(0, &caps, 0, &speakerMode);
		system->setSpeakerMode(speakerMode);
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);

	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER) {
        system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
        result = system->init(100, FMOD_INIT_NORMAL, 0);
    }

	if(result != FMOD_OK) {
		return false;
	}

	system->set3DSettings(1.0f, 1.0f, 1.0f);

	mAudioSystem = system;

	mListener = new AudioListener();

	return true;
}