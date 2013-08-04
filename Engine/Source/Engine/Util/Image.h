#pragma once

#include <Engine/Challenge.h>
#include <FreeImage.h>

namespace challenge
{
	static std::string imagePath = "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Media/";

	class Image
	{
	public:
		Image(std::string filename, bool absolutePath = false);
		~Image();

		void LoadImageData(FREE_IMAGE_FORMAT imageType, std::string filePath);

		BYTE* GetBits() { return mBitmap; }
		int GetWidth() { return mSize.width; }
		int GetHeight() { return mSize.height; }
		Size GetSize() { return mSize; }
		std::string GetFilename() { return mFilename; }
		std::string GetFilepath() { return mFilepath; }

	private:
		Size mSize;
		BYTE *mBitmap;
		std::string mFilename;
		std::string mFilepath;
		FREE_IMAGE_FORMAT mImageType;

		FREE_IMAGE_FORMAT DetermineImageType(std::string extension);
	};
};