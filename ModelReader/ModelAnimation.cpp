#include "Globals.h"
#include "ModelAnimation.h"

namespace model
{
	ModelAnimation::ModelAnimation(std::string name, int startFrame, int endFrame, int duration) :
		mName(name),
		mStartFrame(startFrame),
		mEndFrame(endFrame),
		mDuration(duration)
	{
	}

	ModelAnimation::~ModelAnimation()
	{
	}

	void ModelAnimation::Serialize(std::ostream &out)
	{
		int namelen = mName.size();
		out.write((char *)namelen, sizeof(int));
		out.write(mName.c_str(), namelen);
		out.write((char *)&mStartFrame, sizeof(int));
		out.write((char *)&mEndFrame, sizeof(int));
		out.write((char *)&mDuration, sizeof(int));
	}
};