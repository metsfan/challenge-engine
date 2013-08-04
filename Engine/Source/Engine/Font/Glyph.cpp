#include <Engine/Challenge.h>
#include "Glyph.h"
#include "Font.h"
#include FT_STROKER_H
using namespace challenge;

Glyph::Glyph(FT_Library &library, FT_Face &face, char c, int outlineWidth)
{
	FT_Bitmap bitmap;

	FT_Error error = FT_Load_Char(face, c, FT_LOAD_NO_BITMAP);
	if (error) {
		return;
	}

	mGlyphIndex = FT_Get_Char_Index(face, c);
	int width = face->glyph->bitmap.width;
	int height = face->glyph->bitmap.rows;

	if(outlineWidth > 0) {
		FT_Error error = FT_Load_Char(face, c, FT_LOAD_NO_BITMAP);
		if (error) {
			return;
		}

		FT_Glyph ftglyph;
		FT_Get_Glyph(face->glyph, &ftglyph);

		FT_Stroker stroker;
		FT_Stroker_New(library, &stroker);
		FT_Stroker_Set(stroker, outlineWidth * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
		
		FT_Glyph_StrokeBorder(&ftglyph, stroker, false, true);

		FT_OutlineGlyph olglyph = reinterpret_cast<FT_OutlineGlyph>(ftglyph);
		FT_Outline outline = olglyph->outline;

		RenderSpans(library, &outline);
	} else {
		//FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LIGHT);
		//bitmap = face->glyph->bitmap;
		RenderSpans(library, &face->glyph->outline);
	}
	FT_Glyph_Metrics metrics = face->glyph->metrics;
	if(mSpans.size() > 0) {
		GlyphSpan front = mSpans.front();
		Rect bounds(front.x, front.y, front.x, front.y);
		for(int i = 0; i < mSpans.size(); i++) {
			bounds.Include(mSpans[i].x, mSpans[i].y);
			bounds.Include(mSpans[i].x + mSpans[i].width - 1, mSpans[i].y);
		}

		
	
		width = bounds.Width();
		height = bounds.Height();
		int size = width * height;

		mBuffer = new unsigned char[size];
		memset(mBuffer, 0, size);
		for(int i = 0; i < mSpans.size(); i++) {
			GlyphSpan span = mSpans[i];
			for (int w = 0; w < span.width; ++w)
					mBuffer[(int)((height - 1 - (span.y - bounds.ymin)) * width
					+ span.x - bounds.xmin + w)] = span.coverage;
		}
	}


	/*for(int m = 0; m < bitmap.rows; m++) {
		for(int n = 0; n < bitmap.width; n++) {
			int index = (m * bitmap.width) + n;
			mBuffer[index] = bitmap.buffer[index];
		}
	}*/
	//mSize.height = metrics.height >> 6;
	//mSize.width = face->glyph->advance.x >> 6;
	mSize.height = height;
	mSize.width = width;

	int horiBearingX = metrics.horiBearingX >> 6;
	int horiBearingY = metrics.horiBearingY >> 6;
	mBearing.x = horiBearingX;
	mBearing.y = horiBearingY;

	

	mAdvance.x = face->glyph->advance.x >> 6;
	mAdvance.y = face->glyph->advance.y >> 6;

}

void Glyph::CopyToAtlas(GlyphAtlas &atlas)
{
	atlas.AddGlyph(mBuffer, mSize, mMinTexCoord, mMaxTexCoord);
}

/* Private */

void Glyph::RenderSpans(FT_Library &library, FT_Outline *outline)
{
	FT_Raster_Params params;
	memset(&params, 0, sizeof(params));
	params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	params.gray_spans = Glyph::SpanCallback;
	params.user = this;

	FT_Outline_Render(library, outline, &params);
}

void Glyph::AddSpan(int y, int count, const FT_Span *spans)
{
	for(int i = 0; i < count; i++) {
		mSpans.push_back(GlyphSpan(spans[i].x, y, spans[i].len, spans[i].coverage));
	}
}

void Glyph::SpanCallback(int y, int count, const FT_Span *spans, void *user)
{
	Glyph *glyph = static_cast<Glyph *>(user);
	glyph->AddSpan(y, count, spans);
}