#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Config
	{
	public:
		static const std::string& GetString(const std::string &key)
		{
			return mConfigValues[key];
		}

		static void LoadFile(const std::string &file);

	private:
		static std::map<std::string, std::string> mConfigValues;
	};
};