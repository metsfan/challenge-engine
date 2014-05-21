#pragma once

#include <Challenge/Challenge.h>

#ifndef INFINITY
#define INFINITY 9999999999
#endif

namespace challenge
{
    struct Range {
        uint32_t min, max;
        Range() : min(0), max(0) {}
        Range(uint32_t _min, uint32_t _max) : min(_min), max(_max) {}
        
        bool Contains(uint32_t n) const { return min <= n && n <= max; }
    };
    
    struct FontFile
    {
        FontFile(std::string _filepath) :
            filepath(_filepath)
        {}
        
        void AddRange(Range range) { glyphRanges.push_back(range); }
        
        std::string filepath;
        std::vector<Range> glyphRanges;
    };

	struct FONT_DESC
	{
		friend class FontManager;

		FONT_DESC()
        :Files(), FontFamily(), FontSize(0), HintingEnabled(false)
        {
		}
        
        std::vector<FontFile> Files;
		std::string FontFamily;
		int FontSize;
        bool HintingEnabled;

	private:

		uint64_t GetKey()
        {
				std::stringstream ss;
				ss << FontFamily << ":" << FontSize;
				std::hash<std::string> strhash;
				return strhash(ss.str());
        }
	};

    // Order on these matter - it is used for anchor points.
	enum TextAlignHorizontal
	{
		TextAlignLeft = 0,
        TextAlignCenter = 1,
		TextAlignRight = 2
	};

	enum TextAlignVertical
	{
		TextAlignTop = 0,
		TextAlignMiddle = 1,
		TextAlignBottom = 2
	};

	union FontTexel
	{
        unsigned char a;
	};

    template <typename CharType = char>
	struct FONT_STRING_DESC
	{
		FONT_STRING_DESC()
        :Text(), TextColor(), OutlineColor(), OutlineSize(0), HorizontalAlign(TextAlignLeft), VerticalAlign(TextAlignTop),
        ShadowColor(), ShadowSize(0), ShadowOffset(0,0), LineWidth(0)
        {
		}

		std::basic_string<CharType> Text;
		Vector4f TextColor;
		Vector4f OutlineColor;
        int OutlineSize;
		TextAlignHorizontal HorizontalAlign;
		TextAlignVertical VerticalAlign;
		Vector4f ShadowColor;
		int ShadowSize;
		Point ShadowOffset;
        int LineWidth;
	};
    
    typedef FONT_STRING_DESC<char> FONT_UTF8STRING_DESC;
    typedef FONT_STRING_DESC<char16_t> FONT_UTF16STRING_DESC;
    typedef FONT_STRING_DESC<char32_t> FONT_UTF32STRING_DESC;

	struct GlyphSpan
	{
		GlyphSpan() { }
		GlyphSpan(int _x, int _y, int _width, int _coverage)
		  : x(_x), y(_y), width(_width), coverage(_coverage) {}

		int x, y, width, coverage;
	};

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
		FontPass(FontPassType _type, int _x, int _y, int _outline) :
			type(_type), x(_x), y(_y), outline(_outline){}

        Vector4f color;
		FontPassType type;
		int x;
		int y;
        int outline;
	};

	typedef std::vector<FontPass> TFontPassList;
}
