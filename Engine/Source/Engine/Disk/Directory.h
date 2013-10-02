#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Directory
	{
	public:
		Directory(const std::string &directory, const std::string filter = "*");
		~Directory();
		
		std::vector<std::string> GetFilesList();
		const std::string& GetDirectoryPath() { return mDirectoryPath; }

	private:
		std::string mDirectoryPath;
		std::string mFilter;
	};
};