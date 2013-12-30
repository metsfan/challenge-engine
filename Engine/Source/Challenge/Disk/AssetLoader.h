#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	template <typename T>
	class AssetLoader
	{
	public:
		static std::string GetPathForAsset(const std::wstring &name);
		static std::vector<std::string> GetFilesInDirectory(const std::wstring &directory, const std::wstring &filter);
	};
};