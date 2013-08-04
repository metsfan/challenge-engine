#include <Engine/Challenge.h>
#include "GlyphAtlas.h"
using namespace challenge;

GlyphAtlas::GlyphAtlas(int width, int height) :
	mSize(width, height)
{
	mDataSize = width * height;
	mData = new Byte[mDataSize];
	mCursor = Point(0, 0);
}

GlyphAtlas::~GlyphAtlas()
{
	if(mData) {
		delete[] mData;
	}
}

void GlyphAtlas::AddGlyph(const Byte *data, const Size &size, glm::vec2 &minTexCoord, glm::vec2 &maxTexCoord)
{
	int bmpWidth = size.width * 4;
	if(bmpWidth + mCursor.x > mSize.width) {
		mCursor.y += mShelfHeight + 2;
		mShelfHeight = 0;
		mCursor.x = 0;
	}

	if(size.height + mCursor.y > mSize.height) {
		throw "Atlas is full";
	}

	for(int i = 0; i < size.height; i++) {
		int nIndex = (i * size.width);
		int bIndex = ((i + mCursor.y) * bmpWidth) + mCursor.x;

		memcpy(&mData[bIndex], &data[nIndex], size.width);
		memcpy(&mData[bIndex+1], &data[nIndex+1], size.width);
	}

	minTexCoord.x = (float)mCursor.x / (float)mSize.width;
	minTexCoord.y = (float)mCursor.y / (float)mSize.height;

	maxTexCoord.x = (float)(mCursor.x + bmpWidth) / (float)mSize.width;
	maxTexCoord.y = (float)(mCursor.y + size.height) / (float)mSize.height;

	mCursor.x += size.width + 2;

	if(size.height > mShelfHeight) {
		mShelfHeight = size.height;
	}
}

/*void GlyphAtlas::CopyToTexture(Texture *texture)
{
	texture->LoadData(mData, mDataSize, mSize.width, mSize.height);
}*/
