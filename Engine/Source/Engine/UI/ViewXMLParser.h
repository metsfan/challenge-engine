#pragma once

#include <Engine/Challenge.h>
#include <Engine/Disk/File.h>
#include <Engine/Util/XML/XML.h>

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