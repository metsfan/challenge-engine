#include <Challenge/Challenge.h>
#include "Technique.h"

namespace challenge
{
	Technique::Technique(std::string name) :
		mCurrentPass(0),
		mNumPasses(1),
		mName(name)
	{
	}

	Technique::~Technique()
	{
		for(int i = 0; i < mPasses.size(); i++) {
			delete mPasses[i];
		}
	}

	bool Technique::HasNextPass()
	{
		return mCurrentPass < mNumPasses;
	}

	void Technique::Begin()
	{
		mCurrentPass = 0;
	}

	void Technique::ProcessNextPass(IGraphicsDevice *device, RenderState &state)
	{
		if(mPasses.size() > mCurrentPass) {
			Pass *pass = mPasses[mCurrentPass];
			pass->Apply(device, state);
			mCurrentPass++;
		}
	}

};
