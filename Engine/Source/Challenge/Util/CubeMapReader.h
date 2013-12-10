#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Util/Image.h>

namespace challenge
{
	class CubeMapReader
	{
	public:
		CubeMapReader(std::shared_ptr<Image> cubeMap);
		~CubeMapReader();

		const BYTE* GetBuffer() { return mBuffer; }
		const Size& GetFaceSize() { return mFaceSize; }

	private:
		BYTE *mBuffer;
		Size mFaceSize;

		void WriteFace(int startX, int startY, const BYTE *imageData, Size &imageSize, BYTE *cubeData);
	};
};