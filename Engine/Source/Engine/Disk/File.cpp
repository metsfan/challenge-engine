#include <Engine/Challenge.h>
#include "File.h"

namespace challenge
{
	bool File::ReadData()
	{
		std::ifstream fileStream(mFilepath, std::ios::binary);
		if(!fileStream.good()) {
			return false;
		}

		mData = TByteArray(std::istreambuf_iterator<char>(fileStream),
                                std::istreambuf_iterator<char>());
		mData.push_back('\0');

		fileStream.close();

		return true;
	}
};