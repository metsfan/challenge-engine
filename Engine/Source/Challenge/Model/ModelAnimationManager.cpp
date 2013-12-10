#include <Challenge/Challenge.h>
#include <Challenge/GameApplication.h>
#include <Challenge/Model/ModelManager.h>
#include "ModelAnimationManager.h"
using namespace challenge;

ModelAnimationManager::ModelAnimationManager(ModelManager *manager)
{
	mManager = manager;
}

ModelAnimationManager::~ModelAnimationManager()
{
}

void ModelAnimationManager::StartAnimations()
{
	mAnimationThread = new std::thread(ModelAnimationManager::AnimationThreadCallback, this);
}

void ModelAnimationManager::AnimationThreadCallback(ModelAnimationManager *animManager)
{
	int desiredFPS = 60;
	int frameTime = 1000000000 / desiredFPS;

	while(true) {
		ModelManager *modelManager = animManager->GetModelManager();
		if (modelManager)
		{
			LARGE_INTEGER time1, time2;
			QueryPerformanceCounter(&time1);

			TModelList models = modelManager->GetActiveModels();
			TModelList::iterator it = models.begin();

			while(it != models.end()) {
				Model *nModel = (*it);
				nModel->SetNextFrame(16);
				++it;
			}

			QueryPerformanceCounter(&time2);

			int dif = frameTime - (time2.QuadPart - time1.QuadPart);
			if (dif > 0) {
				Sleep(dif * 0.000001);
			}
		}
	}
}