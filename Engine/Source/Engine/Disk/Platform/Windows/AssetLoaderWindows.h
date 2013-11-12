#pragma once

#include <Engine/Disk/AssetLoader.h>

namespace challenge
{
	template<>
	class AssetLoader<PlatformTypeWin32>
	{
	public:
		static std::string GetPathForAsset(const std::string &name);
		static std::vector<std::string> GetFilesInDirectory(const std::string &directory, const std::string &filter);

	private:
		static HMODULE sModule;
		static std::string sBaseFilePath;
	};
};