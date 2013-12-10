#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shader/Shader.h>
#include <Challenge/Renderer/Shader/InputLayout.h>
#include <Challenge/Renderer/Texture.h>

namespace challenge
{
	class IShaderProgram
	{
	public:
		virtual void SetShader(IShader *shader) = 0;
		virtual void Build() = 0;
		virtual void Use() = 0;
		virtual void SetInputLayout(InputLayout *inputLayout) = 0;

		virtual int GetIndexForConstant(const std::string &name, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const float *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const int *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const glm::vec2 *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const glm::vec3 *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const glm::vec4 *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const glm::mat2 *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const glm::mat3 *val, int count, ShaderType shader) = 0;
		virtual void SetConstantData(int index, const glm::mat4 *val, int count, ShaderType shader) = 0;
		virtual void SetConstantDataStruct(int index, const void *data, int size, ShaderType shader) = 0;
		
		virtual void SetTexture(int index, ITexture *texture, ShaderType shader) = 0;
	};

	typedef std::vector<IShader *> TShaderList;

	class BaseShaderProgram : public IShaderProgram
	{
	public:
		BaseShaderProgram();
		~BaseShaderProgram();

		void SetShader(IShader *shader);

		void SetInputLayout(InputLayout *inputLayout) { mInputLayout = inputLayout; }
		InputLayout* GetInputLayout() { return mInputLayout; }

		IShader* GetShader(ShaderType type);

	protected:
		TShaderList& GetShaders() { return mShaders; }

	private:
		TShaderList mShaders;
		InputLayout *mInputLayout;
	};

	template <typename Renderer>
	class ShaderProgram : public BaseShaderProgram {};
};