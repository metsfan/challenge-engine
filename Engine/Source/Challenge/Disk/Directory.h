#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Directory
	{
	public:
		Directory(const std::wstring &directory, const std::wstring filter = L"*") :
			mDirectoryPath(directory),
			mFilter(filter)
		{
		}

		Directory(const std::string &directory, const std::string filter = "*") :
			Directory(StringUtil::ToWide(directory), StringUtil::ToWide(filter))
		{
		}

		~Directory()
		{
		}
		
		std::vector<std::wstring> GetFilesList()
		{
			return AssetLoader<CurrentPlatform>::GetFilesInDirectory(mDirectoryPath, mFilter);
		}

		const std::wstring& GetDirectoryPath() { return mDirectoryPath; }

	private:
		std::wstring mDirectoryPath;
		std::wstring mFilter;
	};
};