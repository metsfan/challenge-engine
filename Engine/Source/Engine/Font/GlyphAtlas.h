#pragma once

#include <Engine/Challenge.h>
#include "FontTypes.h"

namespace challenge
{
	class GlyphAtlas
	{
	public:
		GlyphAtlas(int width, int height);
		~GlyphAtlas();

		void AddGlyph(const Byte *data, const Size &size, glm::vec2 &minTexCoord, glm::vec2 &maxTexCoord);
		//void CopyToTexture(Texture *texture);

	private:
		Byte *mData;
		int mDataSize;
		int mShelfHeight;
		Size mSize;
		int mTexWidth;
		Point mCursor;
	};
};