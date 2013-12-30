#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Disk/File.h>

namespace challenge
{
	class FileOutputStream
	{
	public:
		FileOutputStream(const std::wstring &filepath);
		FileOutputStream(const std::string &filepath) :
			FileOutputStream(StringUtil::ToWide(filepath))
		{
		}

		~FileOutputStream();

		bool Open();
		void Close();

		void WriteString(const std::string &str);
		void Write(const void *data, size_t size);

		template <typename T>
		void Write(T data)
		{
			if(mStream.is_open()) {
				mStream.write((const char *)&data, sizeof(T));
			}
		}

		const std::wstring& GetFilepath() { return mFilepath; }

	private:
		std::ofstream mStream;
		std::wstring mFilepath;
	};
};


