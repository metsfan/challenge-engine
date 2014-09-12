#pragma once

#include <Challenge/Challenge.h>

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

		template <typename StringType = std::string>
		static bool StartsWith(const StringType &str, const StringType &search)
		{
			return std::equal(str.begin(), str.end(), search.begin());
		}

		template <typename StringType = std::string>
		static bool EndsWith(const StringType &str, const StringType &search)
		{
			return std::equal(search.rbegin(), search.rend(), str.rbegin());
		}
			
		static std::wstring ToWide(const std::string &str)
		{
			std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter;

			return converter.from_bytes(str);
		}

		static std::string ToNarrow(const std::wstring &str)
		{
			std::string outStr;
			for (int i = 0; i < str.length(); i++) {
				outStr += (char) str[i];
			}

			return outStr;
		}

	};
};