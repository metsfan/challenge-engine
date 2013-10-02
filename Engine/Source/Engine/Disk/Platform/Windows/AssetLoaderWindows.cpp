#include <Engine/Challenge.h>
#include "AssetLoaderWindows.h"

namespace challenge
{
	HMODULE AssetLoader<PlatformTypeWindows>::sModule = NULL;
	std::string AssetLoader<PlatformTypeWindows>::sBaseFilePath;

	std::string AssetLoader<PlatformTypeWindows>::GetPathForAsset(const std::string &name)
	{
		if(!sModule) {
			sModule = GetModuleHandle(NULL);

			sBaseFilePath.resize(MAX_PATH);
			GetModuleFileName(sModule, &sBaseFilePath[0], MAX_PATH);

			sBaseFilePath = sBaseFilePath.substr(0, sBaseFilePath.rfind("\\"));
			

			//sBaseFilePath = "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Media/Images/";
		}

		return sBaseFilePath + "/" + name;
	}

	std::vector<std::string> AssetLoader<PlatformTypeWindows>::GetFilesInDirectory(const std::string &directory, const std::string &filter)
	{
		std::vector<std::string> mFiles;

		WIN32_FIND_DATAA fileData;
		HANDLE hd = FindFirstFileA((directory + "/" + filter).c_str(), &fileData);

		if(hd == INVALID_HANDLE_VALUE) {
			return mFiles;
		}

		do {
			if(strcmp(fileData.cFileName, ".") == 0 ||
			strcmp(fileData.cFileName, "..") == 0) 
			{
				continue;
			}

			mFiles.push_back(directory + "/" + fileData.cFileName);
		} while(FindNextFileA(hd, &fileData));

		return mFiles;
	}
};