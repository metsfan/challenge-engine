#pragma once

#include <Challenge/Core/Globals.h>

namespace challenge
{
	typedef glm::dvec2 Vector2;
	typedef glm::dvec3 Vector3;
	typedef glm::dvec4 Vector4;

	typedef glm::ivec2 Vector2i;
	typedef glm::ivec3 Vector3i;
	typedef glm::ivec4 Vector4i;

	typedef glm::vec2 Vector2f;
	typedef glm::vec3 Vector3f;
	typedef glm::vec4 Vector4f;

	typedef glm::dmat2 Matrix2;
	typedef glm::dmat3 Matrix3;
	typedef glm::dmat4 Matrix4;

	typedef glm::mat2 Matrix2f;
	typedef glm::mat3 Matrix3f;
	typedef glm::mat4 Matrix4f;

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

	class Validatable
	{
	public:
		Validatable()
			:mIsValid(false)
		{
		}

		virtual bool IsValid() const { return mIsValid; }

		virtual void Invalidate() { mIsValid = false; }

	protected:

		bool IsValid(bool reset) {
			bool wasValid = mIsValid;
			if (reset)
				mIsValid = true;
			return wasValid;
		}
		void Validate() { mIsValid = true; }

	private:

		bool mIsValid;
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

		Point(const Vector3& p)
			:x(p.x), y(p.y)
		{}

		double Angle(const Point &other)
		{
			Point dif = *this - other;
			return glm::degrees(atan2(dif.x, dif.y)) + 180;
		}

		double Distance(const Point &other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt((dx * dx) + (dy * dy));
		}

		double Distance2(const Point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return (dx * dx) + (dy * dy);
		}

		bool Equals(const Point& other, real epsilon = 0.000001) const
		{
			return glm::epsilonEqual(x, other.x, epsilon) && glm::epsilonEqual(y, other.y, epsilon);
		}

		bool operator==(const Point &other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Point &other) const
		{
			return x != other.x || y != other.y;
		}

		operator Vector3() const
		{
			return Vector3(x, y, 0);
		}

		Point& operator+=(const Point &delta)
		{
			x += delta.x;
			y += delta.y;

			return *this;
		}

		template<typename T>
		Point& operator/=(T value)
		{
			x /= value;
			y /= value;
			return *this;
		}

		Point operator+(const Point &other) const
		{
			return Point(x + other.x, y + other.y);
		}

		Point& operator-=(const Point &delta)
		{
			x -= delta.x;
			y -= delta.y;

			return *this;
		}

		Point operator-(const Point &other) const
		{
			return Point(x - other.x, y - other.y);
		}

		Point operator/(double s) const
		{
			return Point(x / s, y / s);
		}

		Point operator*(double s) const
		{
			return Point(x * s, y * s);
		}

		void operator*=(double s)
		{
			x *= s;
			y *= s;
		}
		real x, y;
	};

	static const Point kZeroPoint;

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

		Size(const Vector2i& vec) :
			width(vec.x), height(vec.y)
		{
		}

		Size(const Point &point) :
			width(point.x), height(point.y)
		{
		}

		bool Equals(const Size& other, real epsilon = 0.000001) const
		{
			return glm::epsilonEqual(width, other.width, epsilon) && glm::epsilonEqual(height, other.height, epsilon);
		}

		double Area() const
		{
			return width * height;
		}

		bool operator==(const Size &other) const
		{
			return width == other.width && height == other.height;
		}
		bool operator!=(Size &other) const
		{
			return width != other.width || height != other.height;
		}

		void operator+=(const Size& s)
		{
			width += s.width;
			height += s.height;
		}

		void operator-=(const Size& s)
		{
			width -= s.width;
			height -= s.height;
		}

		void operator/=(double s)
		{
			width /= s;
			height /= s;
		}

		void operator*=(double s)
		{
			width *= s;
			height *= s;
		}

		Size operator+(const Size& s) const
		{
			return Size(width + s.width, height + s.height);
		}

		Size operator-(const Size& s) const
		{
			return Size(width - s.width, height - s.height);
		}

		Size operator/(real s) const
		{
			return Size(width / s, height / s);
		}

		Size operator*(real s) const
		{
			return Size(width * s, height * s);
		}

		real width, height;
	};

	static const Size kZeroSize;

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

		void Include(real x, real y)
		{
			left = std::min(left, x);
			bottom = std::min(bottom, y);
			right = std::max(right, x);
			top = std::max(top, y);
		}

		real GetWidth() const { return right - left; }
		real GetHeight() const { return top - bottom; }

		real left, bottom, right, top;
	};

	class Bounds
	{
	public:
		Bounds();
		Bounds(const Point &_min, const Point &_max);
		Bounds(real minX, real minY, real maxX, real maxY);
		Bounds(const Point &origin, const Size &size);
		Bounds(const Point& position, const Size& size, const Point& anchorPoint, const Size& offset);

		Point GetCenter() const;
		real Width() const;
		real Height() const;

		Size GetSize() const;
		bool ContainsPoint(const Point &point) const;
		bool ContainsPoint(double x, double y) const;
		bool ContainsBounds(const Bounds &other) const;
		bool IntersectsBounds(const Bounds &other) const;
		bool IntersectsBounds(real minX, real minY, real maxX, real maxY);
		bool Intersection(const Bounds &other, Bounds &outBounds) const;

		Point WrapPoint(const Point& p);
		bool Equals(const Bounds& other, double epsilon = 0.000001) const;
		void Offset(const Point& p);

		bool operator==(const Bounds &other);
		bool operator!=(const Bounds &other);

		Bounds operator +(const Bounds& other);
		Bounds& operator+=(const Bounds &other);
		Bounds& operator+=(const Point &point);
		Bounds& operator*=(double s);
		Bounds operator/(double s) const;
		Bounds operator*(double s) const;

		Point min, max;
	};
};