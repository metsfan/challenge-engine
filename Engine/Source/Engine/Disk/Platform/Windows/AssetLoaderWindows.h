#pragma once

#include <Engine/Disk/AssetLoader.h>

namespace challenge
{
	template<>
	class AssetLoader<PlatformTypeWindows>
	{
	public:
		static std::string GetPathForAsset(const std::string &name);

	private:
		static HMODULE sModule;
		static std::string sBaseFilePath;
	};
};