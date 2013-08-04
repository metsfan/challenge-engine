#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include <boost/algorithm/string.hpp>
#include "Image.h"

namespace challenge
{
	Image::Image(std::string filename, bool absolutePath) :
		mBitmap(NULL)
	{
		mFilename = filename;

		if(absolutePath) {
			mFilepath = filename;
		} else {
			mFilepath = imagePath + filename;
		}

		std::string extension = Util::GetFilenameExtension(filename);
		mImageType = DetermineImageType(extension);
		if(mImageType >= 0) {
			LoadImageData(mImageType, mFilepath);
		}
	}

	Image::~Image()
	{
		if(mBitmap) {
			delete[] mBitmap; 
		}
	}

	void Image::LoadImageData(FREE_IMAGE_FORMAT imageType, std::string filePath)
	{
		FIBITMAP *timg = FreeImage_Load(imageType, filePath.c_str());
		timg = FreeImage_ConvertTo32Bits(timg);
		mSize.width = FreeImage_GetWidth(timg);
		mSize.height = FreeImage_GetHeight(timg);
		BYTE *bitmap = FreeImage_GetBits(timg);

		int bitmapSize = mSize.width * mSize.height * 4;
		mBitmap = new BYTE[bitmapSize];
		memcpy(mBitmap, bitmap, bitmapSize);

		FreeImage_Unload(timg);
	}

	FREE_IMAGE_FORMAT Image::DetermineImageType(std::string extension)
	{
		if(boost::iequals(extension, "gif")) {
			return FIF_GIF;
		} else if(boost::iequals(extension, "jpg")) {
			return FIF_JPEG;
		} else if(boost::iequals(extension, "png")) {
			return FIF_PNG;
		}
		return FIF_UNKNOWN;
	}
};
