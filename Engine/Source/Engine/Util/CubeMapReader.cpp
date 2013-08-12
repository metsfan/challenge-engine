#include <Engine/Challenge.h>
#include "CubeMapReader.h"

namespace challenge
{
	CubeMapReader::CubeMapReader(std::shared_ptr<Image> cubeMap) :
		mBuffer(NULL)
	{
		int width = cubeMap->GetWidth();
		int height = cubeMap->GetHeight();

		mFaceSize.width = width / 4;
		mFaceSize.height = height / 3;

		const TByteArray &imageData = cubeMap->GetBits();

		int faceBytes = mFaceSize.width * mFaceSize.height * 4;
		mBuffer = new BYTE[faceBytes * 6];
		memset(mBuffer, 100, faceBytes * 6);

		Size imageSize(width, height);

		// Right face
		this->WriteFace(mFaceSize.width * 2, mFaceSize.height, &imageData[0], imageSize, &mBuffer[0]);

		// Left face
		this->WriteFace(0, mFaceSize.height, &imageData[0], imageSize, &mBuffer[faceBytes]);

		// Bottom face
		this->WriteFace(mFaceSize.width, mFaceSize.height * 2, &imageData[0], imageSize, &mBuffer[faceBytes * 2]);

		// Top face
		this->WriteFace(mFaceSize.width, 0, &imageData[0], imageSize, &mBuffer[faceBytes * 3]);

		// Front face
		this->WriteFace(mFaceSize.width, mFaceSize.height, &imageData[0], imageSize, &mBuffer[faceBytes * 4]);

		// Back face
		this->WriteFace(mFaceSize.width * 3, mFaceSize.height, &imageData[0], imageSize, &mBuffer[faceBytes * 5]);

		
	}

	void CubeMapReader::WriteFace(int startX, int startY, const BYTE *imageData, Size &imageSize, BYTE *cubeData)
	{
		int endX = startX + mFaceSize.width;
		int endY = startY + mFaceSize.height;

		for(int i = endY - 1, j = 0; i >= startY; i--, j++) {
			int imgIndex = (i * imageSize.width * 4) + (startX * 4);
			int cubeIndex = (j * mFaceSize.width * 4);
			memcpy(&cubeData[cubeIndex], &imageData[imgIndex], mFaceSize.width * 4);
		}
	}

	CubeMapReader::~CubeMapReader()
	{
		if(mBuffer) {
			delete[] mBuffer;
		}
	}
};