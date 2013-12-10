#include <Challenge/Challenge.h>
#include "AudioListener.h"
#include <Challenge/GameApplication.h>
#include <Challenge/Audio/AudioManager.h>
using namespace challenge;

AudioListener::AudioListener()
{
	FMOD_VECTOR up = { 0, 1, 0 };
	mUp = up;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 orientation = glm::vec3(0, 0, -1);
	glm::vec3 velocity = glm::vec3(0, 0, 0);

	SetPosition(position);
	SetOrientation(orientation);
}

AudioListener::~AudioListener()
{
}

void AudioListener::SetPosition(glm::vec3 position)
{
	FMOD_VECTOR fmodVec = { position.x, position.y, position.z };
	mPosition = fmodVec;
	Update();
}

void AudioListener::SetOrientation(glm::vec3 orientation)
{
	FMOD_VECTOR fmodVec = { orientation.x, orientation.y, orientation.z };
	mOrientation = fmodVec;
	Update();
}

void AudioListener::SetVelocity(glm::vec3 velocity)
{
	FMOD_VECTOR fmodVec = { velocity.x, velocity.y, velocity.z };
	mVelocity = fmodVec;
	Update();
}

void AudioListener::Update()
{
	FMOD_RESULT result;
	FMOD::System *system = GameApplication::GetInstance()->GetAudioManager()->GetAudioSystem();
	result = system->set3DListenerAttributes(0, &mPosition, &mVelocity, &mOrientation, &mUp);
}