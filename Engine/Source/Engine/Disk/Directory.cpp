#include <Engine/Challenge.h>
#include <Engine/Disk/Directory.h>

namespace challenge
{
	Directory::Directory(const std::string &directory, const std::string filter) :
		mDirectoryPath(directory),
		mFilter(filter)
	{
	}

	Directory::~Directory()
	{
	}

	std::vector<std::string> Directory::GetFilesList()
	{
		return AssetLoader<PlatformTypeWindows>::GetFilesInDirectory(mDirectoryPath, mFilter);
	}
};