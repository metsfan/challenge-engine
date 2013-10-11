#pragma once

#include <Engine/Challenge.h>
#include <Engine/Disk/File.h>

namespace challenge
{
	class FileOutputStream
	{
	public:
		FileOutputStream(const std::string &filepath);
		~FileOutputStream();

		bool Open();
		void Close();

		void Write(const void *data, size_t size);

		template <typename T>
		void Write(T data)
		{
			if(mStream.is_open()) {
				mStream.write((const char *)&data, sizeof(T));
			}
		}

		const std::string& GetFilepath() { return mFilepath; }

	private:
		std::ofstream mStream;
		std::string mFilepath;
	};
};


