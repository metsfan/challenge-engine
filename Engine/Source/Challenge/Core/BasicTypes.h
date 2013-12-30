#pragma once

#include <Challenge/Core/Globals.h>

namespace challenge
{

	class PlatformType {};
	class PlatformTypeWin32 : public PlatformType {};

	class RendererType {};
	class RendererTypeDX11 : public RendererType {};
	class RendererTypeOpenGL : public RendererType {};

#ifdef WINDOWS
	typedef PlatformTypeWin32 CurrentPlatform;
#endif

#ifndef BYTE
	typedef unsigned char BYTE;
#endif

	enum ImageType
	{
		ImageTypeUnknown,
		ImageTypePNG,
		ImageTypeJPEG
	};

	typedef std::vector<BYTE> TByteArray;

	class Size
	{
	public:
		Size() :
			width(0), height(0)
		{
		}

		Size(real _width, real _height) :
			width(_width), height(_height)
		{
		}

		bool operator==(const Size &other) const
		{
			return other.width == width && other.height == height;
		}

		real width, height;
	};

	class Point
	{
	public:
		Point() :
			x(0), y(0)
		{
		}

		Point(real _x, real _y) :
			x(_x), y(_y)
		{
		}

		bool operator==(const Point &other) const
		{
			return other.x == x && other.y == y;
		}

		Point operator-(const Point &other) const
		{
			return Point(x - other.x, y - other.y);
		}

		Point& operator-=(const Point &other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Point operator+(const Point &other) const
		{
			return Point(x + other.x, y + other.y);
		}

		Point& operator+=(const Point &other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Point operator*(const Point &other) const
		{
			return Point(x * other.x, y * other.y);
		}

		Point& operator*=(const Point &other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		Point operator/(const Point &other) const
		{
			return Point(x / other.x, y / other.y);
		}

		Point& operator/=(const Point &other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		real x, y;
	};

	class Frame
	{
	public:
		Frame()
		{
		}

		Frame(const Point &_origin, const Size &_size) :
			origin(_origin), size(_size)
		{
		}

		Frame(real _x, real _y, real _width, real _height) :
			origin(_x, _y), size(_width, _height)
		{
		}

		bool operator==(const Frame &other) const
		{
			return other.size == size && other.origin == origin;
		}

		bool Contains(const Point &other) const
		{
			return !(origin.x > other.x ||
				origin.y > other.y ||
				origin.x + size.width < other.x ||
				origin.y + size.height < other.y);
		}

		Point origin;
		Size size;
	};

	class Rect
	{
	public:
		Rect() :
			left(0), bottom(0), right(0), top(0)
		{
		}

		Rect(real _left, real _bottom, real _right, real _top) :
			left(_left), bottom(_bottom), right(_right), top(_top)
		{
		}

		real left, bottom, right, top;
	};

	class Color
	{
	public:
		Color()
		{
		}

		Color(float _red, float _green, float _blue, float _alpha) :
			red(_red * 255.0f), green(_green * 255.0f), 
			blue(_blue * 255.0f), alpha(_alpha * 255.0f)
		{
		}

		Color(int _red, int _green, int _blue, int _alpha) :
			red(_red), green(_green), blue(_blue), alpha(_alpha)
		{
		}

		static Color FromHexString(const std::string &hex)
		{
			Color color;
			if(hex.length() == 6) {
				unsigned int hexInt;
				std::stringstream ss;
				ss << std::hex << hex;
				ss >> hexInt;
				color.red = hexInt >> 16;
				color.green = (hexInt << 8) >> 24;
				color.blue = (hexInt << 16) >> 24;
				color.alpha = 255;
			}
			return color;
		}

		operator glm::vec4()
		{
			return glm::vec4(red / 255.0f, green / 255.0f, 
				blue / 255.0f, alpha / 255.0f);
		}

		static Color White()
		{
			static Color whiteColor(255, 255, 255, 255);
			return whiteColor;
		}

		static Color Black()
		{
			static Color whiteColor(0, 0, 0, 255);
			return whiteColor;
		}

		static Color Red()
		{
			static Color redColor(255, 0, 0, 255);
			return redColor;
		}

		static Color Green()
		{
			static Color redColor(0, 255, 0, 255);
			return redColor;
		}

		static Color Blue()
		{
			static Color redColor(0, 0, 255, 255);
			return redColor;
		}

		static Color Yellow()
		{
			static Color redColor(255, 255, 0, 255);
			return redColor;
		}

		static Color Magenta()
		{
			static Color redColor(255, 0, 255, 255);
			return redColor;
		}

		static Color Cyan()
		{
			static Color redColor(0, 255, 255, 255);
			return redColor;
		}

		static Color Clear()
		{
			static Color redColor(0, 0, 0, 0);
			return redColor;
		}

		static Color Orange()
		{
			static Color redColor(255, 127, 0, 255);
			return redColor;
		}

		static Color Purple()
		{
			static Color redColor(128, 0, 128, 255);
			return redColor;
		}

		static Color Brown()
		{
			static Color redColor(150, 75, 0, 255);
			return redColor;
		}

		static Color Gray()
		{
			static Color redColor(128, 128, 128, 255);
			return redColor;
		}

		int red, green, blue, alpha;
	};
};