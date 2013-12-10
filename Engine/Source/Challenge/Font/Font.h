#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/Glyph.h>
#include <Challenge/Font/FontTypes.h>
#include <Challenge/Font/FontFace.h>
#include <Challenge/Util/Util.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace challenge
{
	static const int kBottomBuffer = 5;

	typedef std::map<int, Glyph *> TGlyphMap;
    
    template <typename CharType>
    class GlyphAtlas;

	class FontCache;
    
	class StringBuffer
	{
		friend class Font;
	public:
		StringBuffer() :
			mBuffer(NULL),
			mSize() {}

		~StringBuffer()
		{
			/*if(mBuffer != NULL) {
				delete mBuffer;
			}*/
		}

		const BYTE* GetBuffer() { return mBuffer; }
		const Size& GetSize() const { return mSize; }

	private:
		BYTE *mBuffer;
		Size mSize;
	};

	class Font
	{
        friend class Glyph;
        
	public:
		Font(FONT_DESC &fontDesc);
		~Font();

        template <typename CharType>
		StringBuffer CreateStringBitmap(FONT_STRING_DESC<CharType> fontStringDesc);
		
		template <typename CharType>
		GlyphAtlas<CharType>* CreateGlyphAtlas(FONT_STRING_DESC<CharType> fontStringDesc, Size atlasSize);

		long GetKerning(Glyph *leftGlyph, Glyph *rightGlyph);
        int GetKerning(int leftChar, int rightChar);
		Glyph* GetGlyph(int character, bool outline = false);
		Glyph* GetGlyphForPass(FontPass &pass, int character);

		int GetMaxCharHeight() { return mFaces[0]->GetMaxCharHeight(); }
        int GetLineHeight() { return mFaces[0]->GetLineHeight(); }
		Size GetStringDimensions(const std::string &str);
		
		static FT_Library sFTLibrary;

		/* Static Getters */
		static Font* GetFont(const std::string &name, int size);
		static Font* GetFont(FONT_DESC &fontDesc);

	private:
        std::vector<FontFace *> mFaces;
		TGlyphMap mGlyphs;
		TGlyphMap mOutlineGlyphs;
		int mMaxHeight;
		FONT_DESC mFontDesc;

		template <typename CharType>
		void BuildStringBuffer(FONT_STRING_DESC<CharType> &fontStringDesc, StringBuffer &stringBuffer, std::function<void(Glyph*, Point&, Point&)> *charAddedFunc = NULL);

		template <typename CharType>
		TFontPassList GetPasses(FONT_STRING_DESC<CharType> &fontStringDesc);
		
		static std::string sFontPath;
		static FontCache sGlobalFontCache;
	};
};

#include <Challenge/Font/Font.inl>

