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
};