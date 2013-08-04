#include <Engine/Challenge.h>
#include "GraphicsContext.h"
#include <Engine/Renderer/Shader/Shader.h>
#include <Engine/Renderer/Shader/ShaderProgram.h>
#include <Engine/Renderer/Texture.h>

namespace challenge
{
	BaseGraphicsContext::BaseGraphicsContext()
	{
	}

	BaseGraphicsContext::~BaseGraphicsContext()
	{
		TShaderCacheMap::iterator shaderIt = mShaders.begin();
		while(shaderIt != mShaders.end()) {
			delete (*shaderIt).second;
		}

		TShaderProgramCacheMap::iterator programIt = mShaderPrograms.begin();
		while(programIt != mShaderPrograms.end()) {
			delete (*programIt).second;
		}

		for(auto it : mEffects) {
			delete it.second;
		}
	}

	void BaseGraphicsContext::AddShader(std::string key, IShader *shader)
	{
		if(this->GetShader(key)) {
			delete mShaders[key];
		}

		mShaders[key] = shader;
	}

	IShader* BaseGraphicsContext::GetShader(std::string key)
	{
		return mShaders[key];
	}

	void BaseGraphicsContext::AddShaderProgram(std::string key, IShaderProgram *program)
	{
		mShaderPrograms[key] = program;
	}

	IShaderProgram* BaseGraphicsContext::GetShaderProgram(std::string key)
	{
		return mShaderPrograms[key];
	}

	void BaseGraphicsContext::AddEffect(std::string key, Effect *technique)
	{
		mEffects[key] = technique;
	}

	Effect* BaseGraphicsContext::GetEffect(std::string key)
	{
		return mEffects[key];
	}

	void BaseGraphicsContext::SetActiveShaderProgram(IShaderProgram *shader)
	{
		if(mActiveShader != shader) {
			shader->Use();
			mActiveShader = shader;
		}
	}

	void BaseGraphicsContext::SetActiveTexture(ITexture *texture, int slot)
	{
	}
};