#pragma once

#include <Engine/Challenge.h>
#include <Engine/Util/Image.h>

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

		void WriteFace(int startX, int startY, BYTE *imageData, Size &imageSize, BYTE *cubeData);
	};
};