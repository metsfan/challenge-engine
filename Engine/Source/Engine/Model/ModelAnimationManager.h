#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class ModelManager;

	class ModelAnimationManager
	{
	public:
		ModelAnimationManager(ModelManager *manager);
		~ModelAnimationManager();

		void StartAnimations();

		ModelManager* GetModelManager() { return mManager; }

		static void AnimationThreadCallback(ModelAnimationManager *animManager);

	private:
		std::thread *mAnimationThread;
		ModelManager *mManager;
	};
};