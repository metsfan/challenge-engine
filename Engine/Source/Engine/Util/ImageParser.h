#pragma once

#include <Engine/Challenge.h>
#include <Engine/Util/Image.h>

namespace challenge
{
	class ImageParser
	{
	public:
		static bool Parse(const TByteArray &data, ImageBitmap &outData);

	private:
		static bool ParsePNG(const TByteArray &data, ImageBitmap &outData);
		static bool ParseJPEG(const TByteArray &data, ImageBitmap &outData);

		static ImageType DetermineImageType(const TByteArray &data);
	};
};