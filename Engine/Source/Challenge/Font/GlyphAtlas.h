#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/Glyph.h>
#include <Challenge/Font/FontTypes.h>
#include <Challenge/Font/Font.h>

namespace challenge
{
	struct GlyphData
	{
		Vector2 minCoordinate;
		Vector2 maxCoordinate;
        Size size;
		int page;
        int advance;
        Point bearing;
        int maxHeight;
	};

	typedef std::map<int, GlyphData> TGlyphEntryMap;
    
    static const Point kBaseOffset(3, 2);

	template <typename CharType>
	class GlyphAtlas
	{
	public:
		GlyphAtlas(FONT_STRING_DESC<CharType> fontStringDesc, Font *font, Size size, TFontPassList passes);
		~GlyphAtlas();

		void AddGlyph(int character);
        bool ContainsGlyph(int character) { return mGlyphs.count(character); }
		const void* GetData() { return static_cast<void *>(&mData[0]); }
		const Size& GetSize() const { return mSize; }
		const int GetNumAtlases() { return mNumAtlases; }
		const GlyphData GetCoordinates(int character);
        long GetKerning(int leftChar, int rightChar);
        Font* GetFont() { return mFont; }
        bool UpdatedAfter(long time) { return mLastUpdated > time; }
        float GetUsage() { return (float)mCursor.y / (float)mSize.height; }
        void Empty();

	private:
		FONT_STRING_DESC<CharType> mFontStringDesc;
		std::vector<FontTexel> mData;
		int mDataSize;
		int mShelfHeight;
		Size mSize;
		int mTexWidth;
		Point mCursor;
		Font *mFont;
		int mNumAtlases;
		TFontPassList mPasses;
		TGlyphEntryMap mGlyphs;
        long mLastUpdated;
	};
    
    typedef GlyphAtlas<char> GlyphAtlas8;
    typedef GlyphAtlas<char16_t> GlyphAtlas16;
    typedef GlyphAtlas<char32_t> GlyphAtlast32;
    
}

#include <Challenge/Font/GlyphAtlas.inl>
