#include <Challenge/Challenge.h>
#include <Challenge/GameApplication.h>
#include <Challenge/Model/Model.h>
#include "ModelAnimationManager.h"

namespace challenge
{
	std::vector<Model *> ModelAnimationManager::mModels;

	ModelAnimationManager::ModelAnimationManager()
	{
		mAnimationThread = new RunLoop(30, [this](int deltaMillis) {
			for (Model *model : mModels) {
				model->SetNextFrame(deltaMillis);
			}
		});
	}

	ModelAnimationManager::~ModelAnimationManager()
	{
	}
}

