#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shader/ShaderProgram.h>

namespace challenge
{
	BaseShaderProgram::BaseShaderProgram(IGraphicsDevice *device) :
		GraphicsObject(device),
		mInputLayout(NULL),
		mShaders(kShaderTypeMax + 1)
	{
		for (int i = 0; i < mShaders.size(); i++) {
			mShaders[i] = NULL;
		}
	}

	BaseShaderProgram::~BaseShaderProgram()
	{
		delete mInputLayout;
	}
		
	void BaseShaderProgram::SetShader(IShader *shader)
	{
		mShaders[shader->GetType()] = shader;
	}

	IShader* BaseShaderProgram::GetShader(ShaderType type)
	{
		return mShaders[type];
	}

	void BaseShaderProgram::UpdateState(RenderState &state)
	{
		for (int i = 0; i < mShaders.size(); i++) {
			if (mShaders[i]) {
				mShaders[i]->UpdateState(this, state);
			}
		}
	}
};