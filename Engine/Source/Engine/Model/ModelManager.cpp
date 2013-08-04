#include <Engine/Challenge.h>
#include "ModelManager.h"
using namespace challenge;

int ModelManager::s_NextModelId = 0;

ModelManager::ModelManager()
{
	mAnimManager = NULL;
}

bool ModelManager::Initialize()
{
	mAnimManager = new ModelAnimationManager(this);
	mAnimManager->StartAnimations();

	return true;
}

bool ModelManager::LoadModel(std::string modelName, std::string filename)
{
	/*Model *newModel = new Model();
	if(newModel->Initialize(filename)) {
		mModels[modelName] = newModel;
		return true;
	}*/
	return false;
}

void ModelManager::UnloadModel(std::string modelName)
{
	Model *model = mModels[modelName];
	if(model) {
		mModels.erase(modelName);
	}
}

void ModelManager::AddModel(Model *model)
{
	mActiveModels.push_back(model);
}