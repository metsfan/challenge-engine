#pragma once

#include <Engine/Challenge.h>
#include <ft2build.h>
#include <glm/glm.hpp>
#include "FontTypes.h"
#include "GlyphAtlas.h"
#include FT_FREETYPE_H 

namespace challenge
{
	typedef std::vector<GlyphSpan> TSpanList;

	class Glyph
	{
		friend class Font;

	public:
		Glyph(FT_Library &library, FT_Face &face, char c, int outlineWidth);

		void CopyToAtlas(GlyphAtlas &atlas);

	private:
		Size mSize;
		Point mBearing;
		Point mAdvance;
		glm::vec2 mMinTexCoord;
		glm::vec2 mMaxTexCoord;
		unsigned char *mBuffer;
		unsigned int mGlyphIndex;
		TSpanList mSpans;

		void RenderSpans(FT_Library &library, FT_Outline *outline);
		void AddSpan(int y, int count, const FT_Span *spans);

		static void SpanCallback(int y, int count, const FT_Span *spans, void *user);


	};
};