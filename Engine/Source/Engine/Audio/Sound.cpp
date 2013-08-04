#include <Engine/Challenge.h>
#include "Sound.h"
#include <Engine/Util/Util.h>
#include <Engine/Util/Logger.h>
#include <Engine/GameApplication.h>
#include <Engine/Audio/AudioManager.h>

using namespace challenge;

Sound::Sound(std::string filename, glm::vec3 position, bool loop)
{
	FMOD_VECTOR velocity = { 0, 0, 0 };
	FMOD_VECTOR pos = { position.x, position.y, position.z };

	AudioManager *audioManager = GameApplication::GetInstance()->GetAudioManager();
	FMOD::System *system = audioManager->mAudioSystem;

	FMOD_RESULT result;

	mFilepath = kSoundDir + filename;
	mPosition = pos;
	mVelocity = velocity;

	result = system->createSound(mFilepath.c_str(), FMOD_3D, 0, &mSound);
	if(result != FMOD_OK) {
		//TODO: Error handling
	}

	result = system->playSound(FMOD_CHANNEL_FREE, mSound, true, &mChannel);
	if(result != FMOD_OK) {
		//TODO: Error handling
	}

	Update();

	SetLooping(loop);
}

Sound::~Sound()
{
	mSound->release();
}

void Sound::Play()
{
	mChannel->setPaused(false);
}

void Sound::Stop()
{
	Pause();
	Rewind();
}

void Sound::Pause()
{
	mChannel->setPaused(true);
}

void Sound::Rewind()
{
	mChannel->setPosition(0, FMOD_TIMEUNIT_MS);
}

void Sound::SetVolume(float volume)
{
	mChannel->setVolume(CLAMP(volume, 0, 1));
}

void Sound::SetLooping(bool looping)
{
	if(looping) {
		mSound->setMode(FMOD_LOOP_NORMAL);
	} else {
		mSound->setMode(FMOD_LOOP_OFF);
	}
}

void Sound::SetPosition(glm::vec3 position)
{
	FMOD_VECTOR fmodVec = { position.x, position.y, position.z };
	mPosition = fmodVec;
	Update();
}

void Sound::SetVelocity(glm::vec3 velocity)
{
	FMOD_VECTOR fmodVec = { velocity.x, velocity.y, velocity.z };
	mVelocity = fmodVec;
	Update();
}

void Sound::Update()
{
	mChannel->set3DAttributes(&mPosition, &mVelocity);
}