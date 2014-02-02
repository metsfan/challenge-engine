#include <Challenge/Challenge.h>
#include <Challenge/Core/Color.h>

#include <ahote/hsb.h>

namespace challenge
{
	Color Color::FromHSV(int hue, double saturation, double value)
	{
		double r, g, b;
		ahote::hsb_to_rgb(hue, saturation, value, r, g, b);

		return Color(r * 255, g * 255, b * 255, 255);
	}
};