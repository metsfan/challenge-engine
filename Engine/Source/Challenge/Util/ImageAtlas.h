#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class ImageAtlas
	{
	public:
		ImageAtlas();
		ImageAtlas(const Size &size);
		ImageAtlas(const std::string &name, float texelOffset = 0.0);
		~ImageAtlas();

		void SetTexelOffset(float offset) { mTexelOffset = offset; }
		void SetSizeOffset(float offset) { mSizeOffset = offset; }

		const Frame& GetTexCoords(const std::string &image) 
		{
			if(mImageFrames.find(image) != mImageFrames.end()) {
				return mImageFrames[image];
			}

			return Frame();
		}

		const Size GetImageSize(const std::string &image)
		{
			if(mImageSizes.find(image) != mImageSizes.end()) {
				return mImageSizes[image];
			}

			return Size();
		}

		std::shared_ptr<Image> GetImage() { return mImage; }

		void AddImage(const std::string name, const Frame &frame)
		{
			Frame texFrame((frame.origin.x + mTexelOffset) / (mSize.width - mSizeOffset), 
				(frame.origin.y + mTexelOffset) / (mSize.height - mSizeOffset), 
				(frame.size.width + mTexelOffset) / (mSize.width - mSizeOffset), 
				(frame.size.height + mTexelOffset) / (mSize.height - mSizeOffset));
			mImageFrames[name] = texFrame;
			mImageSizes[name] = frame.size;
		}

		void SetSize(int width, int height)
		{
			mSize.width = width;
			mSize.height = height;
		}

	private:
		std::shared_ptr<Image> mImage;
		Size mSize;
		std::unordered_map<std::string, Frame> mImageFrames;
		std::unordered_map<std::string, Size> mImageSizes;
		float mTexelOffset;
		float mSizeOffset;
	};
};