#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/FontTypes.h>

namespace challenge
{
	class Font;

	typedef std::map<int, Font *> TFontMap;
	class FontCache
	{
	public:
		FontCache();
		~FontCache();

		Font* AddFont(FONT_DESC &fontDesc);
		Font* GetFont(FONT_DESC &fontDesc);
		std::string GetFontKey(std::string name, int size);

	private:
		TFontMap mFonts;
	};
};