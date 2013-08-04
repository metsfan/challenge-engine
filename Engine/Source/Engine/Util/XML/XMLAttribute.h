#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class XMLAttribute
	{
	public:
		XMLAttribute();
		XMLAttribute(const std::string &name, std::string &value);
		~XMLAttribute();

		const std::string& GetName() { return mName; }
		const std::string& GetValue() { return mValue; }

		void SetName(const std::string &name) { mName = name; }
		void SetValue(const std::string &value) { mValue = value; }

	private:
		std::string mName;
		std::string mValue;
	};
};