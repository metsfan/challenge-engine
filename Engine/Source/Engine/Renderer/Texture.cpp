#include <Engine/Challenge.h>
#include "Texture.h"

namespace challenge
{
	BaseTexture::BaseTexture()
	{
	}

	BaseTexture::~BaseTexture()
	{
	}

	bool BaseTexture::Initialize(Image *image)
	{
		return this->Initialize(image->GetBits(), image->GetSize());
	}

	bool BaseTexture::Initialize(const BYTE *buffer, const Size &size)
	{
		std::vector<const BYTE *> buffers;
		buffers.push_back(buffer);

		return this->Initialize(buffers, size);
	}

	bool BaseTexture::Initialize(std::vector<const BYTE *> &buffers, const Size &size)
	{
		mSize = Size(size.width, size.height);
		if(this->LoadTextureData(buffers)) {
			mLoaded = true;
		}

		return true;
	}
};
