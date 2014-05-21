#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Pass.h>

namespace challenge
{
	Pass::Pass() :
		mShader(NULL)
	{
	}

	Pass::~Pass()
	{
	}

	void Pass::Apply(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();

		if(mShader) {
			context->SetActiveShaderProgram(mShader);

			mShader->UpdateState(state);
		}
	}
};