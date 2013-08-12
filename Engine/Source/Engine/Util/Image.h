#pragma once

#include <Engine/Challenge.h>
#include <Engine/Disk/Asset.h>

namespace challenge
{
	static std::string imagePath = "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Media/";

	struct ImageBitmap
	{
		TByteArray data;
		Size size;
	};

	class Image
	{
	public:
		Image(File *file);
		Image(std::string filename);
		~Image();

		void LoadImageData(const TByteArray &data);

		const TByteArray& GetBits() { return mBitmap.data; }
		int GetWidth() { return mBitmap.size.width; }
		int GetHeight() { return mBitmap.size.height; }
		Size GetSize() { return mBitmap.size; }
		std::string GetFilepath() { return mFilepath; }

	private:
		ImageBitmap mBitmap;
		std::string mFilepath;
		ImageType mImageType;
	};
};