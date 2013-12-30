#include "Image.h"

#include <Challenge/Challenge.h>
#include <Challenge/Util/Util.h>
#include <Challenge/Util/ImageParser.h>

namespace challenge
{
	Image::Image(File *file)
	{
		mFilepath = file->GetFilepath();

		this->LoadImageData(file->GetData());
	}

	Image::Image(const std::wstring &filename)
	{
		mFilepath = filename;

		File file(filename);
		if(file.ReadData()) {
			this->LoadImageData(file.GetData());
		} else {
			throw "Failed to read image!";
		}
	}

	Image::~Image()
	{
	}

	void Image::LoadImageData(const TByteArray &data)
	{
		if(!ImageParser::Parse(data, mBitmap)) {
			throw "Failed to read image!";
		}
	}
};
