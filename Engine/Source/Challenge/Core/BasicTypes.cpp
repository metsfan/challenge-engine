#include <Challenge/Challenge.h>

namespace challenge
{
	Bounds::Bounds() :
		min(Point()), max(Point())
	{
	}

	Bounds::Bounds(const Point &_min, const Point &_max) :
		min(_min), max(_max)
	{
	}

	Bounds::Bounds(real minX, real minY, real maxX, real maxY) :
		min(Point(minX, minY)), max(Point(maxX, maxY))
	{
	}

	Bounds::Bounds(const Point &origin, const Size &size) :
		min(origin), max(
		Point(origin.x + size.width,
		origin.y + size.height))
	{
	}

	Bounds::Bounds(const Point& position, const Size& size, const Point& anchorPoint, const Size& offset)
	{
		Point anchorOffset(size.width, size.height);
		anchorOffset.x *= anchorPoint.x;
		anchorOffset.y *= anchorPoint.y;
		min = position;

		min -= anchorOffset;
		max = min + Point(size.width, size.height);
	}

	Point Bounds::GetCenter() const
	{
		return Point((min.x + max.x) / 2.0, (min.y + max.y) / 2.0);
	}

	real Bounds::Width() const
	{
		return max.x - min.x;
	}
	real Bounds::Height() const
	{
		return max.y - min.y;
	}
	Size Bounds::GetSize() const
	{
		return Size(Width(), Height());
	}

	bool Bounds::ContainsPoint(const Point &point) const
	{
		return !(min.x > point.x || min.y > point.y || max.x < point.x
			|| max.y < point.y);
	}

	bool Bounds::ContainsPoint(double x, double y) const
	{
		return !(min.x > x || min.y > y || max.x < x || max.y < y);
	}

	bool Bounds::ContainsBounds(const Bounds &other) const
	{
		return !(min.x > other.min.x || max.x < other.max.x
			|| min.y > other.min.y || max.y < other.max.y);
	}

	bool Bounds::IntersectsBounds(const Bounds &other) const
	{
		return !(min.x > other.max.x || max.x < other.min.x
			|| min.y > other.max.y || max.y < other.min.y);
	}

	bool Bounds::IntersectsBounds(real minX, real minY, real maxX, real maxY)
	{
		return !(min.x > maxX || max.x < minX
			|| min.y > maxY || max.y < minY);
	}

	bool Bounds::Intersection(const Bounds &other, Bounds &outBounds) const
	{
		if (!this->IntersectsBounds(other)) {
			return false;
		}

		outBounds.min.x = std::max(min.x, other.min.x);
		outBounds.min.y = std::max(min.y, other.min.y);
		outBounds.max.x = std::max(max.x, other.max.x);
		outBounds.max.y = std::max(max.y, other.max.y);


		return true;
	}

	Point Bounds::WrapPoint(const Point& p)
	{
		return Point(Util::Wrap(p.x, min.x, max.x), Util::Wrap(p.y, min.y, max.y));

	}
	bool Bounds::Equals(const Bounds& other, double epsilon) const
	{
		return min.Equals(other.min, epsilon) && max.Equals(other.max, epsilon);
	}

	void Bounds::Offset(const Point& p)
	{
		min += p;
		max += p;
	}

	bool Bounds::operator==(const Bounds &other)
	{
		return min == other.min && max == other.max;
	}

	bool Bounds::operator!=(const Bounds &other)
	{
		return min != other.min || max != other.max;
	}

	Bounds Bounds::operator+ (const Bounds& other)
	{
		Bounds b = other;
		b += *this;
		return b;
	}

	Bounds& Bounds::operator+=(const Bounds &other)
	{
		min.x = std::min(min.x, other.min.x);
		min.y = std::min(min.y, other.min.y);
		max.x = std::max(max.x, other.max.x);
		max.y = std::max(max.y, other.max.y);

		return *this;
	}

	Bounds& Bounds::operator+=(const Point &point)
	{
		min.x = std::min(min.x, point.x);
		min.y = std::min(min.y, point.y);
		max.x = std::max(max.x, point.x);
		max.y = std::max(max.y, point.y);

		return *this;
	}

	Bounds Bounds::operator/(double s) const
	{
		return Bounds(min / s, max / s);
	}

	Bounds Bounds::operator*(double s) const
	{
		return Bounds(min * s, max * s);
	}

	Bounds& Bounds::operator*=(double s)
	{
		min *= s;
		max *= s;
		return *this;
	}
}
