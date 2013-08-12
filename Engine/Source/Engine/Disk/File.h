#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class File
	{
	public:
		File(const std::string &path) :
			mFilepath(path)
		{
		}

		~File()
		{
		}

		bool ReadData();
		const TByteArray& GetData() { return mData; }
		const std::string& GetFilepath() { return mFilepath; }

	private:
		std::string mFilepath;
		TByteArray mData;
	};
};