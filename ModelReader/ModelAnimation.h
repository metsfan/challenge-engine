#pragma once

#include "Globals.h"

namespace model
{
	class ModelAnimation
	{
	public:
		ModelAnimation(std::string name, int startFrame, int endFrame, int duration);
		~ModelAnimation();

		void Serialize(std::ostream &out);

	private:
		std::string mName;
		int mStartFrame;
		int mEndFrame;
		int mDuration;
	};
};