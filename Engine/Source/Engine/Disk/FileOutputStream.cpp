#include <Engine/Challenge.h>
#include <Engine/Disk/FileOutputStream.h>

namespace challenge
{
	FileOutputStream::FileOutputStream(const std::string &filepath) :
		mFilepath(filepath)
	{
	}

	FileOutputStream::~FileOutputStream()
	{
	}

	bool FileOutputStream::Open()
	{
		mStream.open(mFilepath.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);

		return mStream.is_open();
	}

	void FileOutputStream::Close()
	{
		mStream.close();
	}

	void FileOutputStream::Write(const void *data, size_t size)
	{
		if(mStream.is_open()) {
			mStream.write((char *)data, size);
		}
	}
};

