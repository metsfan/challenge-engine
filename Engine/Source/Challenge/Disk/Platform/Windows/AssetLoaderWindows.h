#pragma once

#include <Challenge/Disk/AssetLoader.h>

namespace challenge
{
	template<>
	class AssetLoader<PlatformTypeWin32>
	{
	public:
		static std::wstring GetPathForAsset(const std::wstring &name);
		static std::vector<std::wstring> GetFilesInDirectory(const std::wstring &directory, const std::wstring &filter);

	private:
		static HMODULE sModule;
		static std::wstring sBaseFilePath;
	};
};