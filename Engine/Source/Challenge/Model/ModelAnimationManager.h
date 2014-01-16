#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Core/RunLoop.h>

namespace challenge
{
	class Model;

	class ModelAnimationManager
	{
	public:
		ModelAnimationManager();
		~ModelAnimationManager();

		void AddModel(Model *model)
		{
			mModels.push_back(model);
		}

	private:
		RunLoop *mAnimationThread;
	
		static std::vector<Model *> mModels;
	};
};