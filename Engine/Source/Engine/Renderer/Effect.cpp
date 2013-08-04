#include <Engine/Challenge.h>
#include <Engine/Renderer/Effect.h>

namespace challenge
{
	Effect::Effect(std::string name) :
		mName(name),
		mActiveTechnique(NULL)
	{
	}

	Effect::~Effect()
	{
	}

	void Effect::SetActiveTechnique(std::string name)
	{
		if(name != mActiveTechnique->GetName()) {
			if(mTechniques.count(name) > 0) {
				mActiveTechnique = mTechniques[name];
			}
		}
	}

	void Effect::AddTechnique(Technique *technique)
	{
		mTechniques[technique->GetName()] = technique;

		if(!mActiveTechnique) {
			mActiveTechnique = technique;
		}
	}
};