#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	enum LightSourceType
	{
		LightSourceDirectional,
		LightSourcePoint,
		LightSourceSpotlight
	};

	class LightSource
	{
	public:
		LightSource(LightSourceType type) :
			mType(type)
		{
		}

		~LightSource()
		{
		}

		const LightSourceType GetType() { return mType; }

		void SetIntensity(float intensity) { mIntensity = intensity; }
		const float GetIntensity() const { return mIntensity; }

	private:
		LightSourceType mType;
		float mIntensity;
	};


};