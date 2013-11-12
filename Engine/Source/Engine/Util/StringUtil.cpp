#include <Engine/Challenge.h>
#include <Engine/Util/StringUtil.h>

namespace challenge
{
	std::vector<std::string> StringUtil::SplitString(const std::string &str, char delim)
	{
		std::string token;
		std::istringstream stream(str);

		std::vector<std::string> tokens;
		while(std::getline(stream, token, delim)) {
			tokens.push_back(token);
		}

		return tokens;
	}
};