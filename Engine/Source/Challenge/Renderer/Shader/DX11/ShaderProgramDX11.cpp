#include <Challenge/Challenge.h>
#include "ShaderProgramDX11.h"
#include <Challenge/Renderer/Shader/DX11/ShaderDX11.h>
#include <Challenge/Renderer/Texture/TextureDX11.h>

namespace challenge
{
	ShaderProgram<RendererTypeDX11>::ShaderProgram(GraphicsDeviceDX11 *device) :
		BaseShaderProgram(),
		mDevice(device)
	{
		for(int i = kShaderTypeMin; i <= kShaderTypeMax; i++) {
			mConstantBuffers.push_back(TBufferList(kShaderDefaultCacheSize));
			mResources.push_back(TShaderResourceList(kShaderDefaultCacheSize));

			for(int j = 0; j < 10; j++) {
				mConstantBuffers[i][j] = NULL;
				mResources[i][j] = NULL;
			}
		}
		
	}

	ShaderProgram<RendererTypeDX11>::~ShaderProgram()
	{
		mDX11InputLayout->Release();
	}

	void ShaderProgram<RendererTypeDX11>::Build()
	{
		IShader *vertexShader = this->GetShader(ShaderTypeVertexShader);
		if(vertexShader) {
			vertexShader->AttachToProgram(this);
			const unsigned char *source = vertexShader->GetShaderSource();
			const int size = vertexShader->GetSourceSize();

			ID3D11Device *device = mDevice->GetD3D11Device();
			ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

			InputLayout *inputLayout = this->GetInputLayout();
			const TInputElementList &elements = inputLayout->GetElements();
			
			std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements;
			for(int i = 0; i < elements.size(); i++) {
				const InputElement &nextElement = elements[i];
				DXGI_FORMAT format;
				switch(nextElement.numComponents) {
				case 1:
					format = DXGI_FORMAT_R32_FLOAT;
					break;

				case 2:
					format = DXGI_FORMAT_R32G32_FLOAT;
					break;

				case 3:
					format = DXGI_FORMAT_R32G32B32_FLOAT;
					break;

				case 4:
					format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					break;
				}

				D3D11_INPUT_ELEMENT_DESC element = {
					nextElement.name.c_str(), 0, format, 0, nextElement.offset, D3D11_INPUT_PER_VERTEX_DATA, 0
				};
				inputElements.push_back(element);
			}

			HRESULT hr = device->CreateInputLayout(&inputElements[0], inputElements.size(), 
									source, size, &mDX11InputLayout);
			if(hr == S_OK) {
				context->IASetInputLayout(mDX11InputLayout);
			}
		}	

		
	}

	/*void ShaderProgram<RendererTypeDX11>::SetConstantBuffer(void *data, int size, int index, ShaderType type)
	{
		// If we don't have enough slots, extend the constant buffer cache
		if(index >= mConstantBuffers[type].size()) {
			TBufferList newConstantBuffers(index + 10);
			std::copy(mConstantBuffers[type].begin(), mConstantBuffers[type].end(), newConstantBuffers.begin());
			mConstantBuffers[type] = newConstantBuffers;
		}

		ID3D11Buffer* constantBuffer = NULL;
		ID3D11Device *device = mDevice->GetD3D11Device();
		ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

		HRESULT hr;
		// If we haven't set this constant buffer yet, create a new buffer, otherwise update the current one
		if(mConstantBuffers[type][index] == NULL) {
			D3D11_BUFFER_DESC matrixBuffer;
			matrixBuffer.ByteWidth = size;
			matrixBuffer.Usage = D3D11_USAGE_DYNAMIC;
			matrixBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			matrixBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			matrixBuffer.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA matrixData;
			matrixData.pSysMem = data;

			hr = device->CreateBuffer(&matrixBuffer, &matrixData, &constantBuffer);

			if(hr == S_OK) {
				switch(type) 
				{
				case ShaderTypeVertexShader:
					context->VSSetConstantBuffers(index, 1, &constantBuffer);
					break;

				case ShaderTypePixelShader:
					context->PSSetConstantBuffers(index, 1, &constantBuffer);
					break;

				case ShaderTypeGeometryShader:
					context->GSSetConstantBuffers(index, 1, &constantBuffer);
					break;

				case ShaderTypeHullShader:
					context->HSSetConstantBuffers(index, 1, &constantBuffer);
					break;

				case ShaderTypeDomainShader:
					context->DSSetConstantBuffers(index, 1, &constantBuffer);
					break;

				case ShaderTypeComputeShader:
					context->CSSetConstantBuffers(index, 1, &constantBuffer);
					break;
				}

				// Cache the new buffer
				mConstantBuffers[type][index] = constantBuffer;
			}
		} else {
			// Update cached buffer
			constantBuffer = mConstantBuffers[type][index];
			D3D11_MAPPED_SUBRESOURCE mapResource;
			context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
			memcpy(mapResource.pData, data, size);
			context->Unmap(constantBuffer, 0);
		}
	}*/

	void ShaderProgram<RendererTypeDX11>::SetResources(ID3D11ShaderResourceView **resourceView, int start, int count, ShaderType type)
	{
		int end = start + count;

		// If we don't have enough slots, extend the resource cache
		if(end >= mResources[type].size()) {
			TShaderResourceList newResources(end + 10);
			std::copy(mResources[type].begin(), mResources[type].end(), newResources.begin());
			mResources[type] = newResources;
		}

		// If this resource view array isnt identical to what's stored, we need to reload
		bool reload = false;
		for(int i = start, j = 0; i < end; i++, j++) {
			if(mResources[type][start] != resourceView[j]) {
				reload = true;
				break;
			}
		}

		// Reload the resource view
		if(reload) {
			ID3D11Device *device = mDevice->GetD3D11Device();
			ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

			switch(type) 
			{
			case ShaderTypeVertexShader:
				context->VSSetShaderResources(start, count, resourceView);
				break;

			case ShaderTypePixelShader: 
				context->PSSetShaderResources(start, count, resourceView);
				break;

			case ShaderTypeGeometryShader:
				context->GSSetShaderResources(start, count, resourceView);
				break;

			case ShaderTypeHullShader:
				context->HSSetShaderResources(start, count, resourceView);
				break;

			case ShaderTypeDomainShader:
				context->DSSetShaderResources(start, count, resourceView);
				break;

			case ShaderTypeComputeShader:
				context->CSSetShaderResources(start, count, resourceView);
				break;
			}

			// Update the resource cache
			for(int i = start, j = 0; i < end; i++, j++) {
				mResources[type][i] = resourceView[j];
			}
		}
	}

	void ShaderProgram<RendererTypeDX11>::Use()
	{
		TShaderList &shaders = this->GetShaders();
		for(IShader *shader : shaders) {
			if(shader) {
				shader->AttachToProgram(this);
			}
		}

		ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();
		context->IASetInputLayout(mDX11InputLayout);
	}

	int ShaderProgram<RendererTypeDX11>::GetIndexForConstant(const std::string &name, ShaderType shader)
	{
		IShader *shaderObj = this->GetShader(shader);
		if(shaderObj) {
			ShaderDX11 *dxShader = dynamic_cast<ShaderDX11 *>(shaderObj);
			if(dxShader) {
				return dxShader->GetVariableIndex(name);
			}
		}

		return -1;
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const float *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0], sizeof(float) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const int *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0], sizeof(int) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const glm::vec2 *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0][0], sizeof(glm::vec2) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const glm::vec3 *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0][0], sizeof(glm::vec3) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const glm::vec4 *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0][0], sizeof(glm::vec4) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const glm::mat2 *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0][0][0], sizeof(glm::mat2) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const glm::mat3 *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0][0][0], sizeof(glm::mat3) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantData(int index, const glm::mat4 *val, int count, ShaderType shader)
	{
		this->SetConstantDataStruct(index, &val[0][0][0], sizeof(glm::mat4) * count, shader);
	}

	void ShaderProgram<RendererTypeDX11>::SetConstantDataStruct(int index, const void *data, int size, ShaderType shader)
	{
		if(index < 0) {
			return;
		}

		IShader *shaderObj = this->GetShader(shader);
		if(shaderObj) {
			ShaderDX11 *dxShader = dynamic_cast<ShaderDX11 *>(shaderObj);
			if(dxShader) {
				dxShader->SetConstantBufferData(index, data, size);
			}
		}
	}

	void ShaderProgram<RendererTypeDX11>::SetTexture(int index, ITexture *texture, ShaderType shader)
	{
		if(index < 0) {
			return;
		}

		TextureDX11 *dxTexture = dynamic_cast<TextureDX11 *>(texture);
		if(dxTexture) {
			ID3D11ShaderResourceView *resource = dxTexture->GetTextureResource();
			this->SetResources(&resource, index, 1, shader);
		}
	}
};