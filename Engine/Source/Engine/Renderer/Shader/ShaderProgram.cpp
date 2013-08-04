#include <Engine/Challenge.h>
#include "ShaderProgram.h"

namespace challenge
{
	BaseShaderProgram::BaseShaderProgram() :
		mInputLayout(NULL),
		mShaders(kShaderTypeMax+1)
	{
		for(int i = 0; i < mShaders.size(); i++) {
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
};