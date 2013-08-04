#include <Engine/Challenge.h>
#include "RenderState.h"

namespace challenge
{
	RenderState::RenderState() :
		mMaterial(NULL),
		mTopTransform(glm::mat4())
	{
	}

	RenderState::~RenderState()
	{
	}

	void RenderState::AddLight(LightSource *light)
	{
		for(int i = 0; i < mLightSources.size(); i++) {
			// Don't add repeat light sources
			if(light == mLightSources[i]) {
				return;
			}
		}

		// Not found, so add it
		mLightSources.push_back(light);
	}

	void RenderState::RemoveLight(LightSource *light)
	{
		// Only first occurence is removed, since we don't allow repeat lights
		for(int i = 0; i < mLightSources.size(); i++) {
			if(light == mLightSources[i]) {
				mLightSources.erase(mLightSources.begin() + i);
				return;
			}
		}
	}
};