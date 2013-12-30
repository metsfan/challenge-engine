#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shader/Shader.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>
#include <Challenge/Renderer/Shader/DX11/ConstantBufferDX11.h>

namespace challenge
{
	struct ShaderConstantVarDX11
	{
		std::string name;
		int cbufferIndex;
		int varIndex;
	};

	struct ShaderResourceVarDX11
	{
		std::string name;
		int resIndex;
	};

	typedef std::vector<ConstantBufferDX11 *> TConstantBufferList;
	typedef std::vector<ShaderConstantVarDX11> TShaderConstantVarList;
	typedef std::vector<ShaderResourceVarDX11> TShaderResourceVarList;

	template<>
	class Shader<RendererTypeDX11> : public BaseShader
	{
	public:
		Shader(GraphicsDeviceDX11 *device, std::wstring filename, ShaderType type);
		~Shader();

		void Load();

		int GetVariableIndex(const std::string &name);
		void SetConstantBufferData(int index, const void *data, const size_t size);

		void AttachToProgram(IShaderProgram *program);

	private:
		ID3D11VertexShader *mVertexShader;
		ID3D11PixelShader *mPixelShader;
		ID3D11GeometryShader *mGeometryShader;
		ID3D11HullShader *mHullShader;
		ID3D11DomainShader *mDomainShader;
		ID3D11ComputeShader *mComputeShader;
		GraphicsDeviceDX11 *mDevice;
		TConstantBufferList mConstantBuffers;
		TShaderConstantVarList mVariables;
		TShaderResourceVarList mResources;
	};

	typedef Shader<RendererTypeDX11> ShaderDX11;
};