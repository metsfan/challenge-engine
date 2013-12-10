#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	class Camera;
	class RenderableSpriteShape;

	class Model3DView : public View
	{
	public:
		Model3DView(Frame frame = Frame());
		~Model3DView();
		
		void SetModel(Model *model);

		void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		Camera * GetCamera() { return mCamera; }

	private:
		Model *mModel;
		Camera *mCamera;
		RenderableSpriteShape *mTargetSprite;
	};
}