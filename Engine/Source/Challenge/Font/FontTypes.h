#pragma once

#include <Challenge/Challenge.h>

#ifndef INFINITY
#define INFINITY 9999999999
#endif

#define NEWLINE_CHAR 10
#define SPACE_CHAR 32
static const float oo255 = 1.0f / 255.0f;

namespace challenge
{
	typedef unsigned char Byte;

	struct Vector2 {
		float x, y;
		Vector2() { x = 0; y = 0; }
		Vector2(float x, float y) : x(x), y(y) {}
	};
    
    struct Range {
        int min, max;
        Range() : min(0), max(0) {}
        Range(int _min, int _max) : min(_min), max(_max) {}
        
        bool Contains(int n) const { return min <= n && n <= max; }
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
		friend class FontCache;

		FONT_DESC() :
			FontSize(0),
			OutlineWidth(0)
		{
		}
        
        std::vector<FontFile> Files;
		std::string FontFamily;
		int FontSize;
		int OutlineWidth;

	private:
		long key;

		long GetKey() {
			if(key == 0) {
				std::stringstream ss;
				ss << FontFamily << ":" << FontSize;
				if(OutlineWidth > 0) {
					ss << ":o" << OutlineWidth;
				}

				std::hash<std::string> strhash;
				key = strhash(ss.str());
			}

			return key;
		}
	};

	enum TextAlignHorizontal
	{
		TextAlignLeft,
		TextAlignRight,
		TextAlignCenter
	};

	enum TextAlignVertical
	{
		TextAlignTop,
		TextAlignMiddle,
		TextAlignBottom
	};
    
    union FontColor
	{
        struct { float r, g, b, a; };
        float color[4];
        
        FontColor()
        {
            this->SetColor(0, 0, 0, 0);
        }
        
        FontColor(float r, float g, float b, float a)
        {
            this->SetColor(r, g, b, a);
        }
        
		void SetColor(float r, float g, float b, float a) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
			color[3] = a;
		}
		float& operator [](int i) { return color[i]; }
	};

	union FontTexel
	{
        struct { unsigned char r, g, b, a; };
        unsigned char color[4];
        
        FontTexel()
        {
            this->SetColor(0, 0, 0, 0);
        }
        
        FontTexel(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        {
            this->SetColor(r, g, b, a);
        }

		void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
			color[3] = a;
		}
		unsigned char& operator [](int i) { return color[i]; }
	};

    template <typename CharType = char>
	struct FONT_STRING_DESC
	{
		FONT_STRING_DESC() :
			LineWidth(kInfinity),
			ShadowSize(0),
			TextColor(0, 0, 0, 1)
		{
		}

		std::basic_string<CharType> Text;
		FontColor TextColor;
		FontColor OutlineColor;
		TextAlignHorizontal HorizontalAlign;
		TextAlignVertical VerticalAlign;
		FontColor ShadowColor;
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

	struct Rect2
	{
		Rect2() { }
		Rect2(float left, float top, float right, float bottom)
		: xmin(left), xmax(right), ymin(top), ymax(bottom) { }

		void Include(float x, float y)
		{
			xmin = std::min<float>(xmin, x);
			ymin = std::min<float>(ymin, y);
			xmax = std::max<float>(xmax, x);
			ymax = std::max<float>(ymax, y);
		}

		float Width() const { return xmax - xmin + 1; }
		float Height() const { return ymax - ymin + 1; }

		float xmin, xmax, ymin, ymax;
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
		FontPass(FontPassType _type, int _x, int _y, FontColor _color) :
			type(_type), x(_x), y(_y), color(_color) {}

		FontPassType type;
		int x;
		int y;
		FontColor color;
	};

	typedef std::vector<FontPass> TFontPassList;
}
