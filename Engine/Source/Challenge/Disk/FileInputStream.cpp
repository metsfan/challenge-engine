#include <Challenge/Challenge.h>
#include <Challenge/Disk/FileInputStream.h>

namespace challenge
{
	FileInputStream::FileInputStream(const std::wstring &filepath) :
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

	int FileInputStream::ReadString(std::string &str)
	{
		if(mStream.is_open()) {
			int size = this->Read<int>();
			str.resize(size);
			mStream.read(&str[0], size);
			return mStream.gcount();
		}

		return 0;
	}

	int FileInputStream::Read(char *buf, size_t size)
	{
		if (mStream.is_open()) {
			mStream.read(buf, size);
			return mStream.gcount();
		}
	}

};

