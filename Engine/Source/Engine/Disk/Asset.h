#pragma once

#include <Engine/Challenge.h>
#include <Engine/Disk/File.h>
#include <Engine/Disk/Platform/Windows/AssetLoaderWindows.h>

namespace challenge
{
	class Asset : public File
	{
	public:
		Asset(const std::string &name) :
			File(AssetLoader<CurrentPlatform>::GetPathForAsset(name)),
			mName(name)
		{
		}

		~Asset()
		{
		}

		const std::string& GetName() { return mName; }

	private:
		std::string mName;
	};
};