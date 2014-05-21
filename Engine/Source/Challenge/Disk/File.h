#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class File
	{
	public:
		File(const std::wstring &path) :
			mFilepath(path)
		{
		}

		File(const std::string &path) :
			File(StringUtil::ToWide(path))
		{
		}

		~File()
		{
		}

		bool ReadData();
		const TByteArray& GetData() { return mData; }
		const std::wstring& GetFilepath() { return mFilepath; }

		static bool Exists(const std::string &filename)
		{
			std::ifstream file(filename);
			return file.good();
		}

	private:
		std::wstring mFilepath;
		TByteArray mData;
	};
};