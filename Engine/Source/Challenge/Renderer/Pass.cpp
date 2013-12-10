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

			for(GlobalVar &var : mGlobals) {
				ShaderData *data = state.GetShaderData(var.semantic);

				if(data) {
					if(var.shaderIndex < 0) {
						var.shaderIndex = mShader->GetIndexForConstant(var.name, var.type);
					}

					if(var.shaderIndex >= 0) {
						data->Apply(mShader, var.shaderIndex, var.type);
					}
				}
			}
		}
	}
};