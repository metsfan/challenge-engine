#include <Challenge/Challenge.h>
#include <Challenge/Disk/FileOutputStream.h>

namespace challenge
{
	FileOutputStream::FileOutputStream(const std::wstring &filepath) :
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

	void FileOutputStream::WriteString(const std::string &str)
	{
		if(mStream.is_open()) {
			this->Write<int>(str.length());
			mStream.write((char *)&str[0], str.length());
		}
	}

	void FileOutputStream::Write(const void *data, size_t size)
	{
		if (mStream.is_open()) {
			mStream.write((char *) data, size);
		}
	}

};

