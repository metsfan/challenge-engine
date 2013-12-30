#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Disk/File.h>
#include <Challenge/Disk/Platform/Windows/AssetLoaderWindows.h>

namespace challenge
{
	class Asset : public File
	{
	public:
		Asset(const std::wstring &name) :
			File(AssetLoader<CurrentPlatform>::GetPathForAsset(name)),
			mName(name)
		{
		}

		Asset(const std::string &name) :
			Asset(StringUtil::ToWide(name))
		{
		}

		~Asset()
		{
		}

		const std::wstring& GetName() { return mName; }

	private:
		std::wstring mName;
	};
};