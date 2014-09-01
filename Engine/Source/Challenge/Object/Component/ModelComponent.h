#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Object/Component/Component.h>

namespace challenge
{
	class ModelComponent : public RenderableComponent
	{
	public:
		ModelComponent(GameObject *owner, Model *model) :
			RenderableComponent(owner),
			mModel(model)
		{
		}

		~ModelComponent()
		{
		}

		std::string GetType() { return "model"; }

		void SetAnimation(const std::string &animation)
		{
			mModel->SetActiveAnimation(animation, false);
		}

		void QueueAnimation(const std::string &animation, bool loop)
		{
			mModel->QueueAnimation(animation, loop);
		}

		void Update(int deltaMillis)
		{
		}

		void Render(IGraphicsDevice *device, RenderState &state)
		{
			if (mModel) {
				mModel->Render(device, state);
			}
		}

		Model * GetModel() { return mModel; }

	private:
		Model *mModel;
	};
};