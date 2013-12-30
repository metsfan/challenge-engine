#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Object/Component/Component.h>

namespace challenge
{
	class ModelComponent : public IRenderableComponent
	{
	public:
		ModelComponent(Model *model) :
			mModel(model)
		{
		}

		~ModelComponent()
		{
		}

		std::string GetType() { return "model"; }

		void Update(int deltaMillis)
		{
		}

		void Render(IGraphicsDevice *device, RenderState &state)
		{
			if (mModel) {
				mModel->Render(device, state);
			}
		}

	private:
		Model *mModel;
	};
};