#include <Challenge/Challenge.h>
#include "SoundGroup.h"
#include <Challenge/GameApplication.h>
#include <Challenge/Audio/AudioManager.h>
#include <Challenge/Audio/Sound.h>
using namespace challenge;

SoundGroup::SoundGroup(std::string name)
{
	FMOD_RESULT result;
	FMOD::System *system = GameApplication::GetInstance()->GetAudioManager()->GetAudioSystem();
	
	result = system->createSoundGroup(name.c_str(), &mSoundGroup);
	if(result != FMOD_OK) {
		// TODO: Error handling
	}

	result = system->createChannelGroup(name.c_str(), &mChannelGroup);
	if(result != FMOD_OK) {
		// TODO: Error handling
	}
}

SoundGroup::~SoundGroup()
{
	mSoundGroup->release();
	mChannelGroup->release();
}

void SoundGroup::AddSound(Sound *sound)
{
	sound->mSound->setSoundGroup(mSoundGroup);
	sound->mChannel->setChannelGroup(mChannelGroup);
	mSounds.push_back(sound);
}

void SoundGroup::Play()
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->Play();
	}
}

void SoundGroup::Pause()
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->Pause();
	}
}

void SoundGroup::Rewind()
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->Rewind();
	}
}

void SoundGroup::Stop()
{
	Pause();
	Rewind();
}

void SoundGroup::SetVolume(float volume)
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->SetVolume(volume);
	}
}

void SoundGroup::SetLooping(bool looping)
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->SetLooping(looping);
	}
}

void SoundGroup::SetPosition(int index, glm::vec3 position)
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->SetPosition(position);
	}
}

void SoundGroup::SetVelocity(int index, glm::vec3 velocity)
{
	for(int i = 0; i < mSounds.size(); i++) {
		mSounds[i]->SetVelocity(velocity);
	}
}

