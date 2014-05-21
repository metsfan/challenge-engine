#pragma once

#include <Challenge/Core/Globals.h>

namespace challenge
{
	class Color
	{
	public:
		Color() :
			red(0), green(0), blue(0), alpha(255)
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
			if (hex.length() == 6) {
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

		/**
		* Calculate color from Hue, Saturation and Value
		* @param hue - The hue, between 0 and 360
		* @param saturation - The saturation percentage, between 0 and 1
		* @param value percentage - The value percentage, between 0 and 1
		*/
		static Color FromHSV(int hue, double saturation, double value);

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
}