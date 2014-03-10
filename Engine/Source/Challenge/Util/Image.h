#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Disk/Asset.h>

namespace challenge
{
	struct ImageBitmap
	{
		TByteArray data;
		Size size;
	};

	class Image
	{
	public:
		Image(File *file);
		Image(const std::wstring &asset);
		Image(const std::string &asset) :
			Image(StringUtil::ToWide(asset))
		{
		}

		~Image();

		void LoadImageData(const TByteArray &data);

		const TByteArray& GetBits() { return mBitmap.data; }
		int GetWidth() { return mBitmap.size.width; }
		int GetHeight() { return mBitmap.size.height; }
		Size GetSize() { return mBitmap.size; }
		std::wstring GetFilepath() { return mFilepath; }

	private:
		ImageBitmap mBitmap;
		std::wstring mFilepath;
		ImageType mImageType;
	};
};