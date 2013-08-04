#include <Engine/Challenge.h>
#include <Engine/Font/FontCache.h>
#include <Engine/Font/Font.h>

namespace challenge
{
	FontCache::FontCache()
	{
	}

	FontCache::~FontCache()
	{
	}

	Font* FontCache::AddFont(FONT_DESC &fontDesc)
	{
		Font *newFont =new Font(fontDesc);
		mFonts[fontDesc.GetKey()] = newFont;
		return newFont;
	}

	Font* FontCache::GetFont(FONT_DESC &fontDesc)
	{
		Font *font;
		if(!mFonts.count(fontDesc.GetKey())) {
			font = AddFont(fontDesc);
		} else {
			font = mFonts[fontDesc.GetKey()];
		}
		return font;
	}

	std::string FontCache::GetFontKey(std::string name, int size)
	{
		std::stringstream ss;
		ss << name;
		ss << ":";
		ss << size;

		return ss.str();
	}
};

