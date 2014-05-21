#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/Font.h>
#include <Challenge/Font/Types.h>

namespace challenge
{
	typedef std::map<uint64_t, Font *> TFontMap;
    typedef std::map<std::string, FONT_DESC> TFontDescMap;
    
	class FontManager
	{
	public:
		static Font* AddFont(FONT_DESC &fontDesc);
		static Font* GetFont(FONT_DESC &fontDesc);
        static Font* GetFont(const std::string &name, int size);
        static Font* GetDefaultFont();
        static void LoadSystemFont(const std::string &name);
        static void LoadFontConfig(const std::string &filename);

        static const std::string kSystemFont;
        static const int kDefaultFontSize;
        
	private:
		static TFontMap mFonts;
        static TFontDescMap mConfigFonts;
        
        static void CopySystemFonts(const std::string &name);
	};
};