#include <Challenge/Challenge.h>
#include <ft2build.h>
#include FT_STROKER_H

#include <Challenge/Font/Glyph.h>
#include <Challenge/Font/Font.h>
#include <Challenge/Font/FontFace.h>

namespace challenge
{
    static const double kOneOver64 = 1.0 / 64.0;
    
    Glyph::Glyph(FT_Library &library, FontFace &fontFace, int c, int outlineWidth, bool hinting) :
    mFont(fontFace)
    {
        mChar = c;
        
        FT_Face &face = fontFace.GetFTFace();

        int flags = FT_LOAD_DEFAULT;
        if (!hinting)
        {
            flags = FT_LOAD_NO_AUTOHINT | FT_LOAD_NO_HINTING;
        }
        
        FT_Error error = FT_Load_Char(face, c, flags);
        if (error) {
            return;
        }
        
        mGlyphIndex = FT_Get_Char_Index(face, c);
        
        // Load The Glyph For Our Character.
        if(FT_Load_Glyph( face, mGlyphIndex, flags ))
            throw std::runtime_error("FT_Load_Glyph failed");
        
        // Move The Face's Glyph Into A Glyph Object.
        FT_Glyph glyph;
        if(FT_Get_Glyph( face->glyph, &glyph ))
            throw std::runtime_error("FT_Get_Glyph failed");
        
        FT_Stroker stroker;
        FT_Stroker_New(library, &stroker);
        FT_Stroker_Set(stroker, outlineWidth * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
        FT_Glyph_StrokeBorder(&glyph, stroker, false, true);
        
        FT_OutlineGlyph olglyph = reinterpret_cast<FT_OutlineGlyph>(glyph);
        
        FT_Outline outline = olglyph->outline;
        
        RenderSpans(library, &outline);
        
        FT_Stroker_Done(stroker);
        
        // Get metrics
        FT_Glyph_Metrics metrics = face->glyph->metrics;
        mAdvance.x = metrics.horiAdvance * kOneOver64;
        mAdvance.y = metrics.vertAdvance * kOneOver64;
        
        mBearing.x = metrics.horiBearingX * kOneOver64;
        mBearing.y = metrics.horiBearingY * kOneOver64;
        
        mSize.x = glm::round(metrics.width * kOneOver64);
        mSize.y = glm::round(metrics.height * kOneOver64);
        
        // Adjust for outline?
        mAdvance.x += outlineWidth;
        
        // Draw spans
        if(mSpans.size() > 0)
        {
            GlyphSpan front = mSpans.front();
            Rect bounds(front.x, front.y, front.x, front.y);
            for(int i = 0; i < mSpans.size(); i++)
            {
                bounds.Include(mSpans[i].x, mSpans[i].y + 1);
                bounds.Include(mSpans[i].x + mSpans[i].width, mSpans[i].y);
            }
            
            int width = bounds.GetWidth();
            int height = bounds.GetHeight();
            
            mDataSize.x = width;
            mDataSize.y = height;
            
            int size = width * height;
            
            mBuffer = new unsigned char[size];
            memset(mBuffer, 0, size);
            for(int i = 0; i < mSpans.size(); i++)
            {
                GlyphSpan &span = mSpans[i];
                for (int w = 0; w < span.width; ++w)
                {
                    mBuffer[(int)((height - 1 - (span.y - bounds.top)) * width
                                  + span.x - bounds.left + w)] = span.coverage;
                }
            }
        }
        FT_Done_Glyph(glyph);
    }
    
    Glyph::~Glyph()
    {
        delete mBuffer;
    }
    
    void Glyph::RenderToBuffer(FontTexel *buffer, Size &size, Point &offset, int lineHeight, Glyph *prevChar)
    {
        if(prevChar) {
            bool useKerning = (prevChar->mChar != NEWLINE_CHAR) && (prevChar->mChar != SPACE_CHAR);
            
            if(useKerning) {
                mBearing.x += mFont.GetKerning(prevChar, this);
            }
        }
        
        for (int m = 0; m < mDataSize.y; m++) {
            for (int n = 0; n < mDataSize.x; n++) {
                int bIndex = ((m + offset.y) * size.width) + (n + offset.x);
                int nIndex = (m * mDataSize.x) + n;
                buffer[bIndex].a = mBuffer[nIndex];
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
