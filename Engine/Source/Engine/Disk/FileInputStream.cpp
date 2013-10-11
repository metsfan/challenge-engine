#include <Engine/Challenge.h>
#include <Engine/Disk/FileInputStream.h>

namespace challenge
{
	FileInputStream::FileInputStream(const std::string &filepath) :
		mFilepath(filepath)
	{
	}

	FileInputStream::~FileInputStream()
	{
	}

	bool FileInputStream::Open()
	{
		mStream.open(mFilepath.c_str(), std::ios::in | std::ios::binary);

		return mStream.is_open();
	}

	void FileInputStream::Close()
	{
		mStream.close();
	}

	int FileInputStream::Read(char *buf, size_t size)
	{
		if(mStream.is_open()) {
			mStream.read(buf, size);
			return mStream.gcount();
		}

		return 0;
	}
};

