#pragma once

namespace challenge
{
	typedef unsigned char Byte;

	/*struct Size {
		int width, height;
		Size() { width = 0; height = 0; }
		Size(int width, int height) : width(width), height(height) {}
	};
	typedef struct Size Size;

	struct Point {
		int x, y;
		Point() { x = 0; y = 0; }
		Point(int x, int y) : x(x), y(y) {}
	};
	typedef struct Point Point;;*/

	struct FONT_DESC
	{
		friend class FontManager;

		FONT_DESC() {
			memset(this, 0, sizeof(*this));
		}

		std::string FontFamily;
		int FontSize;
		int OutlineWidth;

	private:
		int key;

		int GetKey() {
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

	struct CStringBuffer
	{
		void *buffer;
		Size texSize;
		Point texCoord;
		Size realSize;
	};

	struct FontTexel
	{
		unsigned char color[4];

		void SetColor(int r, int g, int b, int a) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
			color[3] = a;
		}
		unsigned char& operator [](int i) { return color[i]; }
	};

	typedef glm::vec4 FontColor;

	struct FONT_STRING_DESC
	{
		FONT_STRING_DESC() { 
			memset(this, 0, sizeof(*this)); 
		}

		std::string Text;
		FontColor TextColor;
		FontColor OutlineColor;
		TextAlignHorizontal HorizontalAlign;
		TextAlignVertical VerticalAlign;
		FontColor ShadowColor;
		int ShadowSize;
		Point ShadowOffset;
	};

	struct GlyphSpan
	{
		GlyphSpan() { }
		GlyphSpan(int _x, int _y, int _width, int _coverage)
		  : x(_x), y(_y), width(_width), coverage(_coverage) {}

		int x, y, width, coverage;
	};

	struct Rect
	{
		Rect() { }
		Rect(float left, float top, float right, float bottom)
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
}
