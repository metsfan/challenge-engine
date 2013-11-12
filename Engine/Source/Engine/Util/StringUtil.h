#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class StringUtil
	{
	public:
		static std::vector<std::string> SplitString(const std::string &str, char delim);

	};
};