#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Disk/File.h>

namespace challenge
{
	class FileInputStream
	{
	public:
		FileInputStream(const std::wstring &filepath);
		FileInputStream(const std::string &filepath) :
			FileInputStream(StringUtil::ToWide(filepath))
		{
		}
		FileInputStream(File *file) :
			FileInputStream(file->GetFilepath())
		{
		}

		~FileInputStream();

		bool Open();
		void Close();

		int ReadLine(std::string &str);
		int ReadString(std::string &str);
		int Read(char *buf, size_t size);
		
		template <typename T>
		T Read()
		{
			T out;
			this->Read((char *)&out, sizeof(T));

			return out;
		}


		const std::wstring& GetFilepath() { return mFilepath; }

	private:
		std::ifstream mStream;
		std::wstring mFilepath;
	};
};


