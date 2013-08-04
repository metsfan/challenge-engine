#pragma once

#include <Engine/Challenge.h>
#include <functional>
#include "Font.h"
#include "FontTypes.h"

namespace challenge
{
	static const std::string kAssetsDir = "C:/gamedev/engine-dev/challenge/challenge/Source/Assets/";
	typedef std::map<int, Font *> TFontMap;
	class FontManager
	{
	public:
		FontManager();
		~FontManager();

		Font* AddFont(FONT_DESC fontDesc);
		Font* GetFont(FONT_DESC fontDesc);
		std::string GetFontKey(std::string name, int size);

		static FontManager* GetInstance();

	private:
		TFontMap mFonts;

		static FontManager *sInstance;
	};
};