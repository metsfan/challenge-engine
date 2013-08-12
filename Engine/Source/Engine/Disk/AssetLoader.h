#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	template <typename T>
	class AssetLoader
	{
	public:
		static std::string GetPathForAsset(const std::string &name);
	};
};