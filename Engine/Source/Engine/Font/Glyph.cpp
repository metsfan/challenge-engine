#include <Engine/Challenge.h>
#include <Engine/Font/Glyph.h>
#include <Engine/Font/FontFace.h>
#include FT_STROKER_H

namespace challenge 
{
	Glyph::Glyph(FT_Library &library, FontFace &fontFace, int c, int outlineWidth) :
		mFont(fontFace)
	{
		FT_Bitmap bitmap;
    
		FT_Face &face = fontFace.GetFTFace();

		FT_Error error = FT_Load_Char(face, c, FT_LOAD_NO_BITMAP);
		if (error) {
			return;
		}

		mGlyphIndex = FT_Get_Char_Index(face, c);
		int width = face->glyph->bitmap.width;
		int height = face->glyph->bitmap.rows;
    
		FT_Glyph_Metrics metrics = face->glyph->metrics;
		mAdvance.x = int(metrics.horiAdvance >> 6);
		mAdvance.y = int(metrics.vertAdvance >> 6);

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

			//mAdvance.x += outlineWidth;
        
			RenderSpans(library, &outline);
        
			FT_Stroker_Done(stroker);
			FT_Done_Glyph(ftglyph);
		} else {
			//FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LIGHT);
			//bitmap = face->glyph->bitmap;
			RenderSpans(library, &face->glyph->outline);
		}
	
		if(mSpans.size() > 0) {
			GlyphSpan front = mSpans.front();
			Rect2 bounds(front.x, front.y, front.x, front.y);
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
		mSize.width = width - mBearing.x;

		int horiBearingX = int(metrics.horiBearingX >> 6);
		int horiBearingY = int(metrics.horiBearingY >> 6);
		mBearing.x = horiBearingX;
		mBearing.y = horiBearingY;
    
		mAdvance.x -= mBearing.x;
    
		//printf("Char: %c\n", c);
		//printf("Bearing: %d\n", mBearing.x);
		//printf("Advance: %d\n", mAdvance.x);
		//printf("Width: %d\n", mSize.width);
    
		mChar = c;


	}

	Glyph::~Glyph()
	{
		delete[] mBuffer;
	}

	void Glyph::RenderToBuffer(FontColor &color, FontTexel *buffer, Size &size, Point &offset, int lineHeight, Glyph *prevChar)
	{
		int yBelowOrigin = (mSize.height - mBearing.y);
		//offset.y = lineHeight - mSize.height + yBelowOrigin + offset.y;
		//printf("%d\n", offset.y);
		//printf("%c, %d\n", mChar, mBearing.x);
 		if(prevChar) {
			bool useKerning = (prevChar->mChar != NEWLINE_CHAR) && (prevChar->mChar != SPACE_CHAR);
                            
			if(useKerning) {                                    
				mBearing.x += mFont.GetKerning(prevChar, this);
			}
		}
                        
		for (int m = 0; m < mSize.height; m++) {
			for (int n = 0; n < mSize.width; n++) {
				int bIndex = ((m + offset.y) * size.width) + (n + offset.x);
				//if(m < size.height && n < size.width) {
				int nIndex = (m * mSize.width) + n;
				if(mBuffer[nIndex] != 0) {
					float alpha = mBuffer[nIndex] * oo255;
					float dst[4] = { buffer[bIndex][0] * oo255, buffer[bIndex][1] * oo255, buffer[bIndex][2] * oo255, alpha };
					float r = ((alpha * color[0]) + ((1 - alpha) * dst[0])) * 255;
					float g = ((alpha * color[1]) + ((1 - alpha) * dst[1])) * 255;
					float b = ((alpha * color[2]) + ((1 - alpha) * dst[2])) * 255;
					float a = std::min<float>(255, (mBuffer[nIndex] * color[3]) + buffer[bIndex][3]);
					buffer[bIndex].SetColor(r, g, b, a);
				}
				//}
			}
		}
	}

	const int Glyph::GetKerning(Glyph *prevChar)
	{
		return mFont.GetKerning(prevChar, this);
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
}