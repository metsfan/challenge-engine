#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Challenge/Challenge.h>
#include <Challenge/Font/Types.h>

namespace challenge
{
	typedef std::vector<GlyphSpan> TSpanList;
    
    class FontFace;

	class Glyph
	{
		friend class Font;
        friend class FontFace;

	public:
		Glyph(FT_Library &library, FontFace &fontFace, int c, int outlineWidth, bool hinting);
        ~Glyph();

		void RenderToBuffer(FontTexel *buffer, Size &size, Point &offset, int lineHeight, Glyph *prevChar = NULL);

		const Point& GetAdvance() const { return mAdvance; }
        Size GetSize() const { return Size(mSize); }
        Size GetDataSize() const { return Size(mDataSize);}
        const Point& GetBearing() const { return mBearing; }
        const int GetKerning(Glyph *prevChar);
        const int GetCharacter() { return mChar; }

	private:
        
		Vector2i mSize;
        Vector2i mDataSize;
		Point mBearing;
		Point mAdvance;
		Vector2 mMinTexCoord;
		Vector2 mMaxTexCoord;
		unsigned char *mBuffer;
		unsigned int mGlyphIndex;
		TSpanList mSpans;
		int mChar;
        FontFace &mFont;

		void RenderSpans(FT_Library &library, FT_Outline *outline);
		void AddSpan(int y, int count, const FT_Span *spans);

		static void SpanCallback(int y, int count, const FT_Span *spans, void *user);


	};
};