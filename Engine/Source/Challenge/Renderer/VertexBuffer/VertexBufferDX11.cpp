#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>
#include "VertexBufferDX11.h"

namespace challenge
{
	VertexBuffer<RendererTypeDX11>::VertexBuffer(GraphicsDevice<RendererTypeDX11> *device, VERTEX_BUFFER_DESC desc) :
		BaseVertexBuffer(),
		mDevice(device),
		mDesc(desc),
		mBuffer(NULL)
	{
	}

	VertexBuffer<RendererTypeDX11>::VertexBuffer(GraphicsDevice<RendererTypeDX11> *device, void *buffer, int size, D3D11_USAGE usage, int stride) :
		BaseVertexBuffer(),
		mDevice(device),
		mStride(stride)
	{
		this->SetData(buffer, size);
	}

	/* IVertexBuffer methods */
	void VertexBuffer<RendererTypeDX11>::SetData(const void *buffer, int size, int stride)
	{
		D3D11_USAGE usage;
		switch(mDesc.Usage) 
		{
		case VertexBufferUsageStatic:
			usage = D3D11_USAGE_IMMUTABLE;
			break;

		case VertexBufferUsageDynamic:
			usage = D3D11_USAGE_DYNAMIC;
			break;

		case VertexBufferUsageDefault:
		default:
			usage = D3D11_USAGE_DEFAULT;
			break;
		}

		UINT cpuFlags = 0;
		if(mDesc.CPUAccess & VertexBufferCPURead) {
			cpuFlags |= D3D11_CPU_ACCESS_READ;
		}
		if(mDesc.CPUAccess & VertexBufferCPUWrite) {
			cpuFlags |= D3D11_CPU_ACCESS_WRITE;
		}

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = size;
		bufferDesc.Usage = usage;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = cpuFlags;
		bufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA subResourceDesc;
		subResourceDesc.pSysMem = buffer;

		ID3D11Device *device = mDevice->GetD3D11Device();
		ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

		HRESULT hr = device->CreateBuffer(&bufferDesc, &subResourceDesc, &mBuffer);
		if(hr != S_OK) {
			// TODO: Error handling
			throw "Failed to create vertex buffer";
		}

		mDesc.Stride = stride;

		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MinLOD = -FLT_MAX;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

		ID3D11SamplerState *samplerState;
		device->CreateSamplerState(&samplerDesc, &samplerState);

		context->PSSetSamplers(0, 1, &samplerState);
	}

	void VertexBuffer<RendererTypeDX11>::UpdateData(const void *buffer, int size, int offset)
	{
		ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

		context->UpdateSubresource(mBuffer, 0, NULL, buffer, size, 1);
		//context->CopySubresourceRegion(mBuffer, 0, 0, 0, 0, buffer, 0, NULL);
	}

	void VertexBuffer<RendererTypeDX11>::Activate()
	{
		Activate(0);
	}

	void VertexBuffer<RendererTypeDX11>::Activate(int offset)
	{
		ID3D11DeviceContext *context = mDevice->GetD3D11DeviceContext();

		context->IASetVertexBuffers(0, 1, &mBuffer, (UINT *)&mDesc.Stride, (UINT *)&offset);
	}
};