#pragma once

#include <Engine/Challenge.h>
#include <boost/thread/thread.hpp>

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
		boost::thread *mAnimationThread;
		ModelManager *mManager;
	};
};