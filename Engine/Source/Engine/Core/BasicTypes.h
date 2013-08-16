#pragma once

#include <Engine/Core/Globals.h>

namespace challenge
{

	class PlatformType {};
	class PlatformTypeWindows : public PlatformType {};

	class RendererType {};
	class RendererTypeDX11 : public RendererType {};
	class RendererTypeOpenGL : public RendererType {};

#ifdef WINDOWS
	typedef PlatformTypeWindows CurrentPlatform;
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

	class Color
	{
	public:
		Color()
		{
		}

		Color(float _red, float _green, float _blue, float _alpha) :
			red(_red / 255.0f), green(_green / 255.0f), 
			blue(_blue / 255.0f), alpha(_alpha / 255.0f)
		{
		}

		Color(int _red, int _green, int _blue, int _alpha) :
			red(_red), green(_green), blue(_blue), alpha(_alpha)
		{
		}

		int red, green, blue, alpha;
	};
};