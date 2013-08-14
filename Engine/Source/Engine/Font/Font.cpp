#include <Engine/Challenge.h>
#include <Engine/Font/Font.h>
#include <Engine/Font/FontCache.h>
#include <Engine/Font/UnicodeRanges.h>

namespace challenge
{
	FT_Library Font::sFTLibrary = NULL;
	std::string Font::sFontPath = "C:/Windows/Fonts/";
	FontCache Font::sGlobalFontCache;

	static const std::string kDefaultFontPath = "C:/Windows/Fonts/";
	static const std::string kTrueTypeExtension = ".ttf";

	Font::Font(FONT_DESC &fontDesc) :
		mFontDesc(fontDesc),
		mMaxHeight(15)
	{

		FT_Error error;
		if(!sFTLibrary) {
			error = FT_Init_FreeType(&sFTLibrary);
			if (error) {
				throw "Error initializing library";
			}
		}

		if(fontDesc.Files.size() == 0) {
			fontDesc.Files.push_back(FontFile(kDefaultFontPath + fontDesc.FontFamily + kTrueTypeExtension));
		}
    
		for (int i = 0; i < fontDesc.Files.size(); i++) {
			std::ifstream ifile(fontDesc.Files[i].filepath);
        
			if(ifile.good()) {
				mFaces.push_back(new FontFace(sFTLibrary, fontDesc.Files[i], fontDesc.FontSize));
			} else {
				printf("Failed to load font at path %s\n", fontDesc.Files[i].filepath.c_str());
			}
        
		}
	}

	Font::~Font()
	{
	}

	long Font::GetKerning(Glyph *leftGlyph, Glyph *rightGlyph)
	{
        if (leftGlyph && rightGlyph) {
            for (int i = 0; i < mFaces.size(); i++) {
                if(mFaces[i]->ContainsGlyph(leftGlyph->GetCharacter())) {
                    FontFace *face = mFaces[i];
                    return face->GetKerning(leftGlyph, rightGlyph);
                }
            }
        }
            
        return 0;
	}
        
    int Font::GetKerning(int leftChar, int rightChar)
    {
        Glyph *leftGlyph = this->GetGlyph(leftChar);
        Glyph *rightGlyph = this->GetGlyph(rightChar);
            
        return this->GetKerning(leftGlyph, rightGlyph);
    }

	Glyph* Font::GetGlyph(int character, bool outline)
	{
		TGlyphMap *map = &mGlyphs;
		if(outline) {
			map = &mOutlineGlyphs;
		}

		Glyph *glyph = NULL;
		if(!map->count(character)) {
            for (int i = 0; i < mFaces.size(); i++) {
                if(mFaces[i]->ContainsGlyph(character)) {
                    int olWidth = outline ? mFontDesc.OutlineWidth : 0;
                    glyph = new Glyph(sFTLibrary, *mFaces[i], character, olWidth);
                    (*map)[character] = glyph;
                    if (glyph->mSize.height > mMaxHeight) {
                        mMaxHeight = glyph->mSize.height;
                    }
                    break;
                }
            }
		} else {
			glyph = (*map)[character];
		}

		return glyph;
	}

	Glyph* Font::GetGlyphForPass(FontPass &pass, int character)
	{
		Glyph *glyph = NULL;

		switch(pass.type)
		{
                            
			case FontPassOutline:
				glyph = this->GetGlyph(character, true);
				break;
                            
			case FontPassShadow:
			case FontPassBuffer:
			case FontPassNormal:
			default:
				glyph = this->GetGlyph(character);
				break;
		}

		return glyph;
	}

	/* Static Getters */
	Font* Font::GetFont(const std::string &name, int size)
	{
		FONT_DESC fontDesc;
		fontDesc.FontFamily = name;
		fontDesc.FontSize = size;
		
		FontFile file(kDefaultFontPath + fontDesc.FontFamily + kTrueTypeExtension);
		file.AddRange(LATIN_RANGE);
		fontDesc.Files.push_back(file);

		return sGlobalFontCache.GetFont(fontDesc);
	}

	Font* Font::GetFont(FONT_DESC &fontDesc)
	{
		return sGlobalFontCache.GetFont(fontDesc);
	}

	Size Font::GetStringDimensions(const std::string &str)
	{
		Size dims;

		for(int i = 0; i < str.length(); i++) {
			Glyph *glyph = this->GetGlyph(str[i]);
			dims.width += glyph->GetAdvance().x;
			dims.height = std::max(dims.height, glyph->GetSize().height);
		}

		return dims;
	}
};