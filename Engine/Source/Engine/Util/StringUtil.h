#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class StringUtil
	{
	public:
		template <typename StringType = std::string>
		static std::vector<StringType> SplitString(const StringType &str, StringType delim)
		{
			std::vector<StringType> tokens;
			size_t pos = 0;

			do {
				size_t newPos = str.find(delim, pos);

				tokens.push_back(str.substr(pos, newPos - pos));

				if (newPos == StringType::npos) {
					break;
				}

				pos = newPos + delim.length();
			} while (true);

			return tokens;
		}

		template <typename StringType = std::string>
		static StringType ReplaceAll(const StringType &str, const StringType &search, const StringType &replace)
		{
			std::basic_ostringstream<StringType::value_type> outStr;

			size_t pos = 0;

			do {
				size_t newPos = str.find(search, pos);

				outStr << str.substr(pos, newPos - pos);

				if (newPos == StringType::npos) {
					break;
				}

				outStr << replace;

				pos = newPos + search.length();
			} while (true);

			return outStr.str();
		}
			
		template <typename InStringType, typename OutStringType>
		static OutStringType ConvertString(const InStringType &str)
		{
			std::wstring_convert<std::codecvt<InStringType::value_type, OutStringType::value_type, std::mbstate_t>> converter;

			return converter.to_bytes(str);
		}
	};
};