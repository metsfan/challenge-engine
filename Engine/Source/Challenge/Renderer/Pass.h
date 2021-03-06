#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/GraphicsDevice.h>
#include <Challenge/Renderer/RenderState.h>

namespace challenge
{
	struct GlobalVar
	{
		GlobalVar(std::string &_name, std::string &_semantic, ShaderType _type) :
			name(_name), semantic(_semantic), type(_type), shaderIndex(-1)
		{
		}

		std::string name;
		std::string semantic;
		int shaderIndex;
		ShaderType type;
	};

	class Pass
	{
	public:
		Pass();
		~Pass();

		void SetShader(IShaderProgram *shader) { mShader = shader; }
		void AddGlobal(std::string name, std::string semantic, ShaderType type) 
		{
			mGlobals.push_back(GlobalVar(name, semantic, type));
		}

		void Apply(IGraphicsDevice *device, RenderState &state);

	private:
		IShaderProgram *mShader;
		std::vector<GlobalVar> mGlobals;
	};
};