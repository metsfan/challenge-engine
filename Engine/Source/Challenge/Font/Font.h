#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <Challenge/Challenge.h>
#include <Challenge/Font/Glyph.h>
#include <Challenge/Font/Types.h>
#include <Challenge/Font/FontFace.h>
#include <Challenge/Util/SafeObject.hpp>

#define NEWLINE_CHAR 10
#define SPACE_CHAR 32

namespace challenge
{
	static const int kBottomBuffer = 5;
	static const float oo255 = 1.0f / 255.0f;

	typedef std::map<uint64_t, Glyph *> TGlyphMap;
    
    class GlyphAtlas;
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

		const void* GetBuffer() { return mBuffer; }
		const Size& GetSize() const { return mSize; }

	private:
		void *mBuffer;
		Size mSize;
	};

	class Font
	{
        friend class FontManager;
        friend class Glyph;
        
	public:
		~Font();
        
        int GetSize() { return mFontDesc.FontSize; }
        const std::string& GetFamily() { return mFontDesc.FontFamily; }

//        template <typename CharType>
//		StringBuffer CreateStringBitmap(FONT_STRING_DESC<CharType> fontStringDesc);
//        
//        template <typename CharType>
//        TFontPassList GetPasses(FONT_STRING_DESC<CharType> &fontStringDesc);
        
		double GetKerning(Glyph *leftGlyph, Glyph *rightGlyph);
        double GetKerning(int leftChar, int rightChar, int leftCharOutlineSize = 0, int rightCharOutlineSize = 0);
		Glyph* GetGlyph(int character, int outlineSize = 0);

		double GetMaxCharHeight()
        {
            if (mFaces.size())
            {
                return mFaces[0]->GetMaxCharHeight();
            }
            
            if (mBackupFont)
            {
                return mBackupFont->GetMaxCharHeight();
            }
            
            return 0;
        }
        
        double GetLineHeight()
        {
            if (mFaces.size())
            {
                return mFaces[0]->GetLineHeight();
            }
            
            if (mBackupFont)
            {
                return mBackupFont->GetMaxCharHeight();
            }
            
            return 0;
        }
        
        double GetSpaceWidth()
        {
            if (mSpaceGlyph)
                return mSpaceGlyph->GetAdvance().x;
            return 0;
        }
        
        double GetFontScale()
        {
            return mScale;
        }
        
		static FT_Library sFTLibrary;

        uint64_t GenerateKey(int character, int outlineSize)
        {
            uint64_t key = character;
            key <<= 32;
            key |= outlineSize;
            return key;
        }
        
        unsigned short GetFontId()
        {
            return mUID;
        }
        
	private:
        
        std::vector<std::shared_ptr<FontFace> > mFaces;
        
        // Filepath -> font face
        static SafeObject<std::map<std::string, std::shared_ptr<FontFace> > > sFontFaces;
        
		TGlyphMap mGlyphs;

		int mMaxHeight;
		FONT_DESC mFontDesc;
        Font *mBackupFont;
        Glyph* mSpaceGlyph;
        double mScale;
        
        unsigned short mUID;
        
        Font(FONT_DESC &fontDesc);
        
        void SetBackupFont(Font *font) { mBackupFont = font; }

		template <typename CharType>
		void BuildStringBuffer(FONT_STRING_DESC<CharType> &fontStringDesc, StringBuffer &stringBuffer, std::function<void(Glyph*, Point&, Point&)> *charAddedFunc = NULL);
		
        static unsigned short sUIDCounter;
	};
};

