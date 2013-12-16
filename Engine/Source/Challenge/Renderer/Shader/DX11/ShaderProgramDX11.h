#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shader/ShaderProgram.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	typedef std::vector<ID3D11Buffer *> TBufferList;
	typedef std::vector<ID3D11ShaderResourceView *> TShaderResourceList;

	struct ShaderResource
	{
		ID3D11ShaderResourceView *resource;
		int index;
		ShaderType type;
	};

	template<>
	class ShaderProgram<RendererTypeDX11> : public BaseShaderProgram
	{
	public:
		ShaderProgram(GraphicsDeviceDX11 *device);
		~ShaderProgram();

		void Build();
		void Use();

		int GetIndexForConstant(const std::string &name, ShaderType shader);
		void SetConstantData(int index, const float *val, int count, ShaderType shader);
		void SetConstantData(int index, const int *val, int count, ShaderType shader);
		void SetConstantData(int index, const glm::vec2 *val, int count, ShaderType shader);
		void SetConstantData(int index, const glm::vec3 *val, int count, ShaderType shader);
		void SetConstantData(int index, const glm::vec4 *val, int count, ShaderType shader);
		void SetConstantData(int index, const glm::mat2 *val, int count, ShaderType shader);
		void SetConstantData(int index, const glm::mat3 *val, int count, ShaderType shader);
		void SetConstantData(int index, const glm::mat4 *val, int count, ShaderType shader);
		void SetConstantDataStruct(int index, const void *data, int size, ShaderType shader);

		void SetTexture(int index, ITexture *texture, ShaderType shader);

		void SetResources(ID3D11ShaderResourceView **resourceView, int start, int count, ShaderType type);

		GraphicsDeviceDX11* GetDevice() { return mDevice; }

	private:
		GraphicsDeviceDX11 *mDevice;
		ID3D11InputLayout *mDX11InputLayout;
		std::vector<TBufferList> mConstantBuffers;
		std::vector<TShaderResourceList> mResources;
		std::vector<ShaderResource> mDXResources;
	};

	typedef ShaderProgram<RendererTypeDX11> ShaderProgramDX11;
};