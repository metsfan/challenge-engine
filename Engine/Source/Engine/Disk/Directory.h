#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Directory
	{
	public:
		Directory(const std::string &directory, const std::string filter = "*") :
			mDirectoryPath(directory),
			mFilter(filter)
		{
		}

		~Directory()
		{
		}
		
		std::vector<std::string> GetFilesList()
		{
			return AssetLoader<CurrentPlatform>::GetFilesInDirectory(mDirectoryPath, mFilter);
		}

		const std::string& GetDirectoryPath() { return mDirectoryPath; }

	private:
		std::string mDirectoryPath;
		std::string mFilter;
	};
};