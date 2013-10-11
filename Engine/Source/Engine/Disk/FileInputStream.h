#pragma once

#include <Engine/Challenge.h>
#include <Engine/Disk/File.h>

namespace challenge
{
	class FileInputStream
	{
	public:
		FileInputStream(const std::string &filepath);
		~FileInputStream();

		bool Open();
		void Close();

		int Read(char *buf, size_t size);
		
		template <typename T>
		T Read()
		{
			T out;
			this->Read((char *)&out, sizeof(T));

			return out;
		}


		const std::string& GetFilepath() { return mFilepath; }

	private:
		std::ifstream mStream;
		std::string mFilepath;
	};
};


