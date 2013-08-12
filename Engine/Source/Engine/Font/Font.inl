#include <Engine/Math/MathUtil.h>
#include <Engine/Util/Util.h>

namespace challenge
{
	template <typename CharType>
	GlyphAtlas<CharType>* Font::CreateGlyphAtlas(FONT_STRING_DESC<CharType> fontStringDesc, Size atlasSize)
	{
		TFontPassList passes = this->GetPasses(fontStringDesc);
		GlyphAtlas<CharType> *atlas = new GlyphAtlas<CharType>(fontStringDesc, this, atlasSize, passes);

		for(int i = 0; i < fontStringDesc.Text.size(); i++) {
			atlas->AddGlyph(fontStringDesc.Text[i]);
		}

		return atlas;
	}
    
    template <typename CharType>
    StringBuffer Font::CreateStringBitmap(FONT_STRING_DESC<CharType> fontStringDesc)
    {
        FT_Error error;
        StringBuffer stringBuffer;
        
        int lineHeight = mMaxHeight + kBottomBuffer;
        int width = 0;
        int height = lineHeight;
        std::basic_string<CharType> string = fontStringDesc.Text;
        const int length = string.size();
        if(length <= 0) {
            return stringBuffer;
        }
        
        
        int lineWidth = 0;
        for (int i = 0; i < length; i++) {
            CharType c = string.at(i);
			Glyph *glyph = this->GetGlyph(c);
            
            if(c == NEWLINE_CHAR ||
               lineWidth + 3 > fontStringDesc.LineWidth) {
                height += lineHeight;
                width = std::max(width, lineWidth);
            } else {
                lineWidth += mGlyphs[c]->mSize.width;
            }
        }
        width = std::max(width, lineWidth);
        
        width = Util::NearestPow2(width*2);
        height = Util::NearestPow2(height*2);
        
        //width = height = MAX(width, height);

		stringBuffer.mSize = Size(width, height);
        
		this->BuildStringBuffer(fontStringDesc, stringBuffer);

		return stringBuffer;
    }

	template <typename CharType>
	void Font::BuildStringBuffer(FONT_STRING_DESC<CharType> &fontStringDesc, StringBuffer &stringBuffer, std::function<void(Glyph*, Point&, Point&)> *charAddedFunc)
	{
		int lineHeight = mMaxHeight+ kBottomBuffer;
		std::basic_string<CharType> string = fontStringDesc.Text;
		const size_t length = string.size();
		int width = stringBuffer.mSize.width;
		int height = stringBuffer.mSize.height;

		if (width == 0 || height == 0) {
			return;
		}

		FontTexel *bitmap = new FontTexel[width * height];
        memset(bitmap, 0, sizeof(FontTexel) * width * height);
        
        TFontPassList passes = this->GetPasses(fontStringDesc);
        
        int strX = 0, strY = 0;
		Point offset;

        for (int i = 0; i < length; i++) {
			CharType c = string.at(i);
			int charAdvance = 0;

			if(c == SPACE_CHAR) {
                strX += mGlyphs[c]->mAdvance.x;
            } else if(c == NEWLINE_CHAR) {
                strY += lineHeight;
                strX = 0;
            } else {
                Glyph *glyph = NULL;
				for(int p = 0; p < passes.size(); p++) {
					FontPass pass = passes[p];
					FontColor color = pass.color;

					glyph = this->GetGlyphForPass(pass, c);
                    
					if(glyph) {
						if (fontStringDesc.LineWidth > 0 &&
							glyph->mAdvance.x + strX > fontStringDesc.LineWidth) {
							strY += lineHeight;
							strX = 0;
						}

						//int x = pass.x;
						//int y = pass.y;
						offset.x = strX + pass.x;
						offset.y = strY + pass.y + (lineHeight - glyph->mBearing.y);
                
						bool newLine = false;
						
						Glyph *prevGlyph = NULL;
						if(i > 0) {
							prevGlyph = mGlyphs[string.at(i-1)];
						}
                        
						glyph->RenderToBuffer(color, bitmap, stringBuffer.mSize, offset, mMaxHeight);
                        
						//glyph = mGlyphs[c];
						//x += glyph->mAdvance.x;
						if(glyph->mAdvance.x > charAdvance) {
							charAdvance = glyph->mAdvance.x;
						}
						//lineHeight = std::max(size.height, lineHeight);
					}
				}
			}
		
			

			strX += charAdvance;
        }
        
        stringBuffer.mBuffer = (BYTE *)bitmap;
	}

	template <typename CharType>
	TFontPassList Font::GetPasses(FONT_STRING_DESC<CharType> &fontStringDesc)
	{
		TFontPassList passes;
		int startX = mFontDesc.OutlineWidth;
        int startY = mFontDesc.OutlineWidth;

		if(mFontDesc.OutlineWidth > 0) {
            passes.push_back(FontPass(FontPassOutline, 0, 0, fontStringDesc.OutlineColor));
        }
        
        if(fontStringDesc.ShadowSize != 0) {
            FontColor shadowColor = fontStringDesc.ShadowColor;
            float factor = 1.0 / abs(fontStringDesc.ShadowSize);
            int absShadowSize = abs(fontStringDesc.ShadowSize);
            int start, end;
            
            if(fontStringDesc.ShadowSize > 0) {
                start = 1;
                end = fontStringDesc.ShadowSize;
            } else {
                start = fontStringDesc.ShadowSize;
                end = 0;
                
                startX += absShadowSize;
                startY += absShadowSize;
            }
            
            if(fontStringDesc.ShadowOffset.x < 0) {
                startX += fontStringDesc.ShadowOffset.x;
            }
            
            if(fontStringDesc.ShadowOffset.y < 0) {
                startY += fontStringDesc.ShadowOffset.y;
            }
            
            for(int i = start; i <= end; i++) {
                int x, y;
                
                if(i > 0) {
                    shadowColor[3] = 1.0 - (factor * (i - 1));
                    x = mFontDesc.OutlineWidth - i + fontStringDesc.ShadowOffset.x;
                    y = mFontDesc.OutlineWidth - i + fontStringDesc.ShadowOffset.y;
                } else {
                    shadowColor[3] = 1.0 + (factor * i);
                    x = absShadowSize - (mFontDesc.OutlineWidth + abs(i) + fontStringDesc.ShadowOffset.x);
                    y = absShadowSize + (mFontDesc.OutlineWidth + abs(i) + fontStringDesc.ShadowOffset.y);
                }
                
                passes.push_back(FontPass(FontPassShadow, x, y, shadowColor));
            }
            
            
        } else {
            FontColor bufferColor = fontStringDesc.TextColor;
            bufferColor[3] = 0.3;
            //passes.push_back(FontPass(FontPassBuffer, startX + 1, startY, bufferColor));
        }
        
        passes.push_back(FontPass(FontPassNormal, startX, startY, fontStringDesc.TextColor));

		return passes;
	}
};
