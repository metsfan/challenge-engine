#pragma once

#include <Engine/Challenge.h>
#include <ft2build.h>
#include FT_FREETYPE_H 
#include "Glyph.h"
#include "GlyphAtlas.h"
#include "FontTypes.h"

#define NEWLINE_CHAR 10
#define SPACE_CHAR 32

namespace challenge
{
	static int const kBottomBuffer = 5;

	typedef std::map<char, Glyph *> TGlyphMap;

	enum FontPassType
	{
		FontPassOutline,
		FontPassShadow,
		FontPassBuffer,
		FontPassNormal
	};

	struct FontPass
	{
		FontPass() : type(FontPassNormal), x(0), y(0) {}
		FontPass(FontPassType _type, int _x, int _y, FontColor _color) :
			type(_type), x(_x), y(_y), color(_color) {}

		FontPassType type;
		int x;
		int y;
		FontColor color;
	};

	typedef std::vector<FontPass> TFontPassList;

	class Font
	{
	public:
		Font(FONT_DESC fontDesc);
		~Font();

		//void CopyAtlasToTexture(Texture *texture);

		CStringBuffer GetStringBitmap(FONT_STRING_DESC fontStringDesc);

		static FT_Library s_FTLibrary;

	private:
		FT_Face mFace;
		TGlyphMap mGlyphs;
		TGlyphMap mOutlineGlyphs;
		int mMaxHeight;
		GlyphAtlas mGlyphAtlas;
		FONT_DESC mFontDesc;

		
		static std::string s_FontPath;
	};
};