#pragma once

#include <Challenge/Challenge.h>
#include <D3Dcompiler.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	struct CBVariable
	{
		std::string name;
		int offset;
		int size;
	};

	typedef std::vector<CBVariable> TCBVariableList;

	class ConstantBufferDX11
	{
	public:
		ConstantBufferDX11(GraphicsDeviceDX11 *device,
							ID3D11ShaderReflectionConstantBuffer *cbuffer, 
							const D3D11_SHADER_INPUT_BIND_DESC &inputDesc,
							ShaderType shaderType);
		~ConstantBufferDX11();

		void SetVariableValue(const std::string &name, const void *value, const size_t size);
		void SetVariableValue(int index, const void *value, const size_t size);
		void SetBufferData(const void *value, const size_t size, const UINT offset = 0);
		void BindBuffer(ID3D11DeviceContext *dxContext);

		void Activate(ID3D11DeviceContext *dxContext);

		bool HasVariableWithName(const std::string &name);

		std::vector<CBVariable>& GetVariables() { return mVariables; }

	private:
		BYTE *mBufferData;
		size_t mBufferSize;
		UINT mBindIndex;
		UINT mBindCount;
		std::vector<CBVariable> mVariables;
		ID3D11Buffer *mD3DBuffer;
		ShaderType mShaderType;
	};
};