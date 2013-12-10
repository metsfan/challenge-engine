#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Disk/File.h>
#include <Challenge/Util/XML/XML.h>

namespace challenge
{
	class ViewXMLParser
	{
	public:
		static View * Parse(File *file);
		static Frame ParseFrame(const std::string &frameStr);
		static Rect ParseRect(const std::string &rectStr);

	private:
		static View * ParseView(XMLNode &node);
		static View * CreateViewForName(const std::string &name);
	};
};