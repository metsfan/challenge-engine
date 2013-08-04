#include <Engine/Challenge.h>
#include "Font.h"
#include <Engine/Math/MathUtil.h>
#include "FontManager.h"
using namespace challenge;
using namespace challenge;

FT_Library Font::s_FTLibrary = NULL;
std::string Font::s_FontPath = "C:/Windows/Fonts/";

Font::Font(FONT_DESC fontDesc) :
	mGlyphAtlas(1024, 1024),
	mFontDesc(fontDesc)
{

	FT_Error error;
	if(!s_FTLibrary) {
		error = FT_Init_FreeType(&s_FTLibrary);
		if (error) {
			// TODO handle errors
		}
	}
	std::string filepath = kAssetsDir + fontDesc.FontFamily + ".ttf";
	error = FT_New_Face(s_FTLibrary, filepath.c_str(), 0, &mFace);
	if (error) {
		
	}

	error = FT_Set_Pixel_Sizes(mFace, 0, fontDesc.FontSize);
	if (error) { 

	}

	std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+-=[]{}\|;:'\"/?.>,<`~ ";
	mMaxHeight = -1;

	for(int i = 32; i <= 127; i++) {
		char c = (char)i;
		Glyph *glyph = new Glyph(s_FTLibrary, mFace, i, 0);
		glyph->CopyToAtlas(mGlyphAtlas);
		mGlyphs[c] = glyph;

		int height = glyph->mSize.height;
		if(height > mMaxHeight) {
			mMaxHeight = height;
		}
	}

	if(fontDesc.OutlineWidth > 0) {
		for(int i = 32; i <= 127; i++) {
		char c = (char)i;
		Glyph *glyph = new Glyph(s_FTLibrary, mFace, i, fontDesc.OutlineWidth);
		glyph->CopyToAtlas(mGlyphAtlas);
		mOutlineGlyphs[c] = glyph;

		int height = glyph->mSize.height;
		if(height > mMaxHeight) {
			mMaxHeight = height;
		}
	}
	}
}

Font::~Font()
{

}

/*void Font::CopyAtlasToTexture(Texture *texture)
{
	mGlyphAtlas.CopyToTexture(texture);
}*/

CStringBuffer Font::GetStringBitmap(FONT_STRING_DESC fontStringDesc)
{
	FT_Error error;
	CStringBuffer stringBuffer;
	
	int lineHeight = mMaxHeight+ kBottomBuffer;
	int width = 0;
	int height = lineHeight;
	std::string string = fontStringDesc.Text;
	const int length = string.size();
	if(length <= 0) {
		return stringBuffer; 
	}


	int lineWidth = 0;
	for (int i = 0; i < length; i++) {
		char c = string.at(i);
		if(c == NEWLINE_CHAR) {
			height += lineHeight;
			width = std::max(width, lineWidth);
		} else {
			lineWidth += mGlyphs[c]->mSize.width;
		}
	}
	width = std::max(width, lineWidth);

	stringBuffer.realSize = Size(width, height);

	width = MathUtil::NearestPow2(width*2);
	height = MathUtil::NearestPow2(height*2);

	//width = height = MAX(width, height);

	FontTexel *bitmap = new FontTexel[width * height];
	memset(bitmap, 0, sizeof(FontTexel) * width * height);

	float width4 = width * 4;
	                                                         
	int maxWidth = mFace->max_advance_width >> 6;
	float oo255 = 1.0f / 255.0f;
	int startX = mFontDesc.OutlineWidth;
	int startY = mFontDesc.OutlineWidth;

	TFontPassList passes;
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
				shadowColor.a = 1.0 - (factor * (i - 1));
				x = mFontDesc.OutlineWidth - i + fontStringDesc.ShadowOffset.x;
				y = mFontDesc.OutlineWidth - i + fontStringDesc.ShadowOffset.y;
			} else {
				shadowColor.a = 1.0 + (factor * i);
				x = absShadowSize - (mFontDesc.OutlineWidth + abs(i) + fontStringDesc.ShadowOffset.x);
				y = absShadowSize + (mFontDesc.OutlineWidth + abs(i) + fontStringDesc.ShadowOffset.y);
			}
			
			passes.push_back(FontPass(FontPassShadow, x, y, shadowColor));
		}

		
	} else {
		FontColor bufferColor = fontStringDesc.TextColor;
		bufferColor.a = 0.2;
		passes.push_back(FontPass(FontPassBuffer, startX + 1, startY, bufferColor));
	}

	passes.push_back(FontPass(FontPassNormal, startX, startY, fontStringDesc.TextColor));

	for(int p = 0; p < passes.size(); p++) {
		FontPass pass = passes[p];
		int x = pass.x;
		int y = pass.y;

		for (int i = 0; i < length; i++) {
			char c = string.at(i);
			if(c == SPACE_CHAR) {
				x += mGlyphs[c]->mAdvance.x;
			} else if(c == NEWLINE_CHAR) {
				y += lineHeight;
				x = pass.x;
			} else {
				Glyph *glyph = NULL;
				FontColor color = pass.color;

				switch(pass.type) 
				{

				case FontPassOutline:
					glyph = mOutlineGlyphs[c];
					break;

				case FontPassShadow:
				case FontPassBuffer:
				case FontPassNormal:
				default:
					glyph = mGlyphs[c];
					break;
				}

				if(glyph) { 
					unsigned char * buffer = glyph->mBuffer;
					Size size = glyph->mSize;
					Point bearing = glyph->mBearing;
					int yBelowOrigin = (size.height - bearing.y);
					int yOffset = mMaxHeight - size.height + yBelowOrigin + y;

					
					if(i > 0) {
						char prevChar = string.at(i-1);
						bool useKerning = (prevChar != NEWLINE_CHAR) && (prevChar != SPACE_CHAR);

						if(useKerning) {
							Glyph *prevGlyph = mGlyphs[prevChar];

							if(prevGlyph) {
								FT_Vector delta;
								FT_Get_Kerning(mFace, prevGlyph->mGlyphIndex, glyph->mGlyphIndex 
									,FT_KERNING_DEFAULT, &delta );

								bearing.x += delta.x >> 6;
							}
						}
					}

					for (int m = 0; m < size.height; m++) {
						for (int n = 0; n < size.width; n++) {
							int bIndex = ((m + yOffset) * width) + (n + x + bearing.x);
							//if(m < size.height && n < size.width) {
								int nIndex = (m * size.width) + n;
								if(buffer[nIndex] != 0) {
									float alpha = buffer[nIndex] * oo255;
									glm::vec3 dst = glm::vec3(bitmap[bIndex][0] * oo255, bitmap[bIndex][1] * oo255, bitmap[bIndex][2] * oo255);
									float r = ((alpha * color.r) + ((1 - alpha) * dst.r)) * 255;
									float g = ((alpha * color.g) + ((1 - alpha) * dst.g)) * 255;
									float b = ((alpha * color.b) + ((1 - alpha) * dst.b)) * 255;
									float a = std::min<float>(255, (buffer[nIndex] * color.a) + bitmap[bIndex].color[3]);
									bitmap[bIndex].SetColor(r, g, b, a);
								}
							//}
						}
					}

					//glyph = mGlyphs[c];
					x += glyph->mAdvance.x;
					//lineHeight = std::max(size.height, lineHeight);
				}
			}
		}
	}

	stringBuffer.buffer = static_cast<void *>(bitmap);
	stringBuffer.texSize = Size(width, height);
	stringBuffer.texCoord = Point(stringBuffer.realSize.width / width, stringBuffer.realSize.height / height);
	
	return stringBuffer;
}