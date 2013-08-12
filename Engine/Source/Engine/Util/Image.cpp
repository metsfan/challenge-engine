#include "Image.h"

#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include <Engine/Util/ImageParser.h>

namespace challenge
{
	Image::Image(File *file)
	{
		mFilepath = file->GetFilepath();

		this->LoadImageData(file->GetData());
	}

	Image::Image(std::string filename)
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
