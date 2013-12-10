#include <Challenge/Challenge.h>
#include "ConstantBufferDX11.h"

namespace challenge
{
	ConstantBufferDX11::ConstantBufferDX11(GraphicsDeviceDX11 *device,
											ID3D11ShaderReflectionConstantBuffer *cbuffer,
											const D3D11_SHADER_INPUT_BIND_DESC &inputDesc,
											ShaderType shaderType)
	{
		ID3D11Device *dxDevice = device->GetD3D11Device();
		ID3D11DeviceContext *dxContext = device->GetD3D11DeviceContext();

		// Create CPU-side buffer
		D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
		cbuffer->GetDesc(&shaderBufferDesc);

		mBufferSize = shaderBufferDesc.Size;
		mBufferData = new BYTE[mBufferSize];
		memset(mBufferData, 0, mBufferSize);

		mBindIndex = inputDesc.BindPoint;
		mBindCount = inputDesc.BindCount;

		int numVars = shaderBufferDesc.Variables;

		// Extract CB variable names and offsets
		for(int i = 0; i < numVars; i++) {
			ID3D11ShaderReflectionVariable *variable = cbuffer->GetVariableByIndex(i);

			CBVariable cbVar;
			D3D11_SHADER_VARIABLE_DESC varDesc;
			variable->GetDesc(&varDesc);
			cbVar.name = std::string(varDesc.Name);
			cbVar.size = varDesc.Size;
			cbVar.offset = varDesc.StartOffset;

			mVariables.push_back(cbVar);
		}

		// Create CB shader resource
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = mBufferSize;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA bufferData;
		bufferData.pSysMem = mBufferData;

		HRESULT hr = dxDevice->CreateBuffer(&bufferDesc, &bufferData, &mD3DBuffer);

		if(hr == S_OK) {
			switch(shaderType) 
			{
			case ShaderTypeVertexShader:
				dxContext->VSSetConstantBuffers(mBindIndex, mBindCount, &mD3DBuffer);
				break;

			case ShaderTypePixelShader:
				dxContext->PSSetConstantBuffers(mBindIndex, mBindCount, &mD3DBuffer);
				break;

			case ShaderTypeGeometryShader:
				dxContext->GSSetConstantBuffers(mBindIndex, mBindCount, &mD3DBuffer);
				break;

			case ShaderTypeHullShader:
				dxContext->HSSetConstantBuffers(mBindIndex, mBindCount, &mD3DBuffer);
				break;

			case ShaderTypeDomainShader:
				dxContext->DSSetConstantBuffers(mBindIndex, mBindCount, &mD3DBuffer);
				break;

			case ShaderTypeComputeShader:
				dxContext->CSSetConstantBuffers(mBindIndex, mBindCount, &mD3DBuffer);
				break;
			}
		} else {
			throw "Error";
		}
	}

	ConstantBufferDX11::~ConstantBufferDX11()
	{
		if(mBufferData) {
			delete mBufferData;
		}

		mD3DBuffer->Release();
	}

	void ConstantBufferDX11::SetVariableValue(const std::string &name, const void *value, const size_t size)
	{
		for(int i = 0; i < mVariables.size(); i++) {
			CBVariable &var = mVariables[i];
			if(var.name == name) {
				this->SetVariableValue(i, value, size);
				return;
			}
		}
	}

	void ConstantBufferDX11::SetVariableValue(int index, const void *value, const size_t size)
	{
		CBVariable &var = mVariables[index];
		this->SetBufferData(value, size, var.offset);
	}

	void ConstantBufferDX11::SetBufferData(const void *value, const size_t size, const UINT offset)
	{
		assert(mBufferSize >= offset + size);

		memcpy(&mBufferData[offset], value, size);
	}

	void ConstantBufferDX11::BindBuffer(ID3D11DeviceContext *dxContext)
	{
		// Update shader resource
		D3D11_MAPPED_SUBRESOURCE mapResource;
		dxContext->Map(mD3DBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
		memcpy(mapResource.pData, mBufferData, mBufferSize);
		dxContext->Unmap(mD3DBuffer, 0);
	}

	bool ConstantBufferDX11::HasVariableWithName(const std::string &name)
	{
		for(CBVariable &var : mVariables) {
			if(var.name == name) {
				return true;
			}
		}

		return false;
	}
};