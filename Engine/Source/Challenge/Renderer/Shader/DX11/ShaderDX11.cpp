#include <Challenge/Challenge.h>
#include "ShaderDX11.h"
#include <Challenge/Renderer/Shader/DX11/ShaderProgramDX11.h>
#include <D3Dcompiler.h>

namespace challenge
{
	Shader<RendererTypeDX11>::Shader(GraphicsDeviceDX11 *device, std::wstring filename, ShaderType type) :
			BaseShader(device, filename + L".cso", type),
			mVertexShader(NULL),
			mPixelShader(NULL),
			mGeometryShader(NULL),
			mHullShader(NULL),
			mDomainShader(NULL),
			mComputeShader(NULL),
			mDevice(device) 
	{
	}

	Shader<RendererTypeDX11>::~Shader()
	{
		for(ConstantBufferDX11 *cbuffer : mConstantBuffers) {
			delete cbuffer;
		}

		if(mVertexShader) mVertexShader->Release();
		if(mPixelShader) mPixelShader->Release();
		if(mGeometryShader) mGeometryShader->Release();
		if(mHullShader) mHullShader->Release();
		if(mDomainShader) mDomainShader->Release();
		if(mComputeShader) mComputeShader->Release();
	}


	void Shader<RendererTypeDX11>::Load()
	{
		const TByteArray &source = this->GetShaderSource();

		ID3D11Device *device = mDevice->GetD3D11Device();

		HRESULT hr;
		switch(this->GetType())
		{
		case ShaderTypeVertexShader:
			{
				hr = device->CreateVertexShader(&source[0], source.size(), NULL, &mVertexShader);
				if(hr != S_OK) {
					throw "Failed to create shader";
				}
			}
			break;

		case ShaderTypePixelShader:
			{
				hr = device->CreatePixelShader(&source[0], source.size(), NULL, &mPixelShader);
				if(hr != S_OK) {
					throw "Failed to create shader";
				}
			}
			break;

		case ShaderTypeGeometryShader:
			{
				hr = device->CreateGeometryShader(&source[0], source.size(), NULL, &mGeometryShader);
				if(hr != S_OK) {
					throw "Failed to create shader";
				}
			}
			break;

		case ShaderTypeHullShader:
			{
				hr = device->CreateHullShader(&source[0], source.size(), NULL, &mHullShader);
				if(hr != S_OK) {
					throw "Failed to create shader";
				}
			}
			break;

		case ShaderTypeDomainShader:
			{
				hr = device->CreateDomainShader(&source[0], source.size(), NULL, &mDomainShader);
				if(hr != S_OK) {
					throw "Failed to create shader";
				}
			}
			break;

		case ShaderTypeComputeShader:
			{
				ID3D11ComputeShader *computeShader = NULL;
				hr = device->CreateComputeShader(&source[0], source.size(), NULL, &mComputeShader);
				if(hr != S_OK) {
					throw "Failed to create shader";
				}
			}
			break;
		}

		ID3D11ShaderReflection *reflection = NULL;
		D3DReflect(&source[0], source.size(), IID_ID3D11ShaderReflection, (void **) &reflection);

		D3D11_SHADER_DESC shaderDesc;
		reflection->GetDesc(&shaderDesc);

		int numConstantBuffers = shaderDesc.ConstantBuffers;
		for(int i = 0; i < numConstantBuffers; i++) {
			ID3D11ShaderReflectionConstantBuffer *cbuffer = reflection->GetConstantBufferByIndex(i);

			D3D11_SHADER_BUFFER_DESC cbufferDesc;
			cbuffer->GetDesc(&cbufferDesc);

			D3D11_SHADER_INPUT_BIND_DESC inputDesc;
			reflection->GetResourceBindingDescByName(cbufferDesc.Name, &inputDesc);

			ConstantBufferDX11 *cbufferObj = new ConstantBufferDX11(mDevice, cbuffer, inputDesc, this->GetType());
			mConstantBuffers.push_back(cbufferObj);

			std::vector<CBVariable> &cbVariables = cbufferObj->GetVariables();

			int j = 0;
			for(CBVariable &var : cbVariables) {
				ShaderConstantVarDX11 cbVar;
				cbVar.name = var.name;
				cbVar.cbufferIndex = i;
				cbVar.varIndex = j;

				mVariables.push_back(cbVar);

				j++;
			}
		}

		int numResources = shaderDesc.BoundResources;
		for(int i = 0; i < numResources; i++) {
			D3D11_SHADER_INPUT_BIND_DESC inputDesc;
			reflection->GetResourceBindingDesc(i, &inputDesc);

			if(inputDesc.Type == D3D_SIT_TEXTURE &&
				inputDesc.Dimension != D3D_SRV_DIMENSION_UNKNOWN) {
				ShaderResourceVarDX11 rsVar;
				rsVar.name = inputDesc.Name;
				rsVar.resIndex = inputDesc.BindPoint;

				mResources.push_back(rsVar);
			}
		}
	}

	void Shader<RendererTypeDX11>::AttachToProgram(IShaderProgram *program)
	{
		ShaderProgram<RendererTypeDX11> *dxShaderProgram = dynamic_cast<ShaderProgram<RendererTypeDX11> *>(program);
		ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

		if(dxShaderProgram) {

			switch(this->GetType())
			{
			case ShaderTypeVertexShader:
				{
					if(mVertexShader) {
						context->VSSetShader(mVertexShader, NULL, 0);
					}
				}
				break;

			case ShaderTypePixelShader:
				{
					if(mPixelShader) {
						context->PSSetShader(mPixelShader, NULL, 0);
					}
				}
				break;

			case ShaderTypeGeometryShader:
				{
					if(mGeometryShader) {
						context->GSSetShader(mGeometryShader, NULL, 0);
					}
				}
				break;

			case ShaderTypeHullShader:
				{
					if(mHullShader) {
						context->HSSetShader(mHullShader, NULL, 0);
					}
				}
				break;

			case ShaderTypeDomainShader:
				{
					if(mDomainShader) {
						context->DSSetShader(mDomainShader, NULL, 0);
					}
				}
				break;

			case ShaderTypeComputeShader:
				{
					if(mComputeShader) {
						context->CSSetShader(mComputeShader, NULL, 0);
					}
				}
				break;
			}
		}

		for(ConstantBufferDX11 *cbuffer : mConstantBuffers) {
			//cbuffer->BindBuffer(mDevice->GetD3D11DeviceContext());
			cbuffer->Activate(context);
		}
	}

	int32_t Shader<RendererTypeDX11>::GetVariableLocalIndex(const std::string &name)
	{
		for(int i = 0; i < mResources.size(); i++) {
			ShaderResourceVarDX11 &var = mResources[i];
			if(var.name == name) {
				return var.resIndex;
			}
		}

		for(int i = 0; i < mVariables.size(); i++) {
			ShaderConstantVarDX11 &var = mVariables[i];
			if(var.name == name) {
				return i;
			}
		}

		return -1;
	}

	void Shader<RendererTypeDX11>::SetConstantBufferData(int index, const void *data, const size_t size)
	{
		ShaderConstantVarDX11 &var = mVariables[index];
		ConstantBufferDX11 *cbuffer = mConstantBuffers[var.cbufferIndex];
		cbuffer->SetVariableValue(var.varIndex, data, size);

		cbuffer->BindBuffer(mDevice->GetD3D11DeviceContext());
	}
};