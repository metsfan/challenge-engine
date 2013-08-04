#include <Engine/Challenge.h>
#include "FontManager.h"
using namespace challenge;

FontManager *FontManager::sInstance = NULL;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

Font* FontManager::AddFont(FONT_DESC fontDesc)
{
	Font *newFont =new Font(fontDesc);
	mFonts[fontDesc.GetKey()] = newFont;
	return newFont;
}

Font* FontManager::GetFont(FONT_DESC fontDesc)
{
	Font *font = mFonts[fontDesc.GetKey()];
	if(!font) {
		font = AddFont(fontDesc);
	}
	return font;
}

std::string FontManager::GetFontKey(std::string name, int size)
{
	std::stringstream ss;
	ss << name;
	ss << ":";
	ss << size;

	return ss.str();
}

FontManager* FontManager::GetInstance()
{
	if(!sInstance) {
		sInstance = new FontManager();
	}
	return sInstance;
}
