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

			sBaseFilePath = "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Media/Images/";
		}

		return sBaseFilePath + name;
	}
};