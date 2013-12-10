#include <Challenge/Challenge.h>
#include <Challenge/GameApplication.h>
#include "Texture2DDX11.h"

namespace challenge
{
	Texture2D<RendererTypeDX11>::Texture2D(GraphicsDeviceDX11 *device, TEXTURE_DESC &desc) :
		TextureDX11(device, desc),
		mDXTexture(NULL)
	{
		ZeroMemory(&mTextureParams, sizeof(D3D11_TEXTURE2D_DESC));
		mTextureParams.MipLevels = 1;
		mTextureParams.ArraySize = 1;
		mTextureParams.Format = DX11TextureFormats[desc.Format];
		mTextureParams.Usage = D3D11_USAGE_DEFAULT;
		mTextureParams.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		mTextureParams.SampleDesc.Count = 1;
		mTextureParams.SampleDesc.Quality = 0;
		mTextureParams.CPUAccessFlags = 0;
		mTextureParams.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	}

	Texture2D<RendererTypeDX11>::~Texture2D()
	{
		if(mDXTexture) {
			mDXTexture->Release();
		}
	}

	bool Texture2D<RendererTypeDX11>::LoadTextureData(std::vector<const BYTE *> &buffers)
	{
		TEXTURE_DESC &desc = this->GetDesc();

		const Size &size = this->GetSize();
		mTextureParams.Width = size.width;
		mTextureParams.Height = size.height;

		D3D11_SUBRESOURCE_DATA textureData;
		textureData.pSysMem = buffers[0];

		textureData.SysMemPitch = size.width * TextureFormatNumComponents[desc.Format];
	
		ID3D11Device *device = this->GetDevice()->GetD3D11Device();
		
		HRESULT hr = device->CreateTexture2D(&mTextureParams, &textureData, &mDXTexture);

		if(hr != S_OK) {
			// TODO: Error handling
			throw "Error Creating D3D11 Texture!";
		}

		ID3D11ShaderResourceView *resourceView;
		D3D11_SHADER_RESOURCE_VIEW_DESC resourceViewDesc;
		memset(&resourceViewDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		resourceViewDesc.Format = mTextureParams.Format;
		resourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		resourceViewDesc.Texture2D.MipLevels = 1;
		resourceViewDesc.Texture2D.MostDetailedMip = 0;

		hr = device->CreateShaderResourceView(mDXTexture, &resourceViewDesc, &resourceView);
		if(hr != S_OK) {
			// TODO: Error handling
			throw "Error Creating D3D11 Texture Resource View!";
		}

		this->SetTextureResource(resourceView);
	}
};