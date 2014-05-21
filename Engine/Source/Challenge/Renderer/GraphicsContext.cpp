#include <Challenge/Challenge.h>
#include "GraphicsContext.h"
#include <Challenge/Renderer/Shader/Shader.h>
#include <Challenge/Renderer/Shader/ShaderProgram.h>
#include <Challenge/Renderer/Texture.h>

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

	int32_t BaseGraphicsContext::RegisterGlobal(const std::string &name)
	{
		auto it = mGlobalDataRegistry.find(name);
		if (it == mGlobalDataRegistry.end()) {
			int index = mGlobalDataRegistry.size();
			mGlobalDataRegistry[name] = index;

			return index;
		}

		return it->second;
	}

	int32_t BaseGraphicsContext::GetGlobalIndex(const std::string &name)
	{
		auto it = mGlobalDataRegistry.find(name);
		if (it != mGlobalDataRegistry.end()) {
			return it->second;
		}

		return -1;
	}
};