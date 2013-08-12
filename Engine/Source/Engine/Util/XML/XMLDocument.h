#pragma once

#include <rapidxml/rapidxml.hpp>

#include <Engine/Challenge.h>
#include <Engine/Util/XML/XMLNode.h>

namespace challenge
{
	enum XMLOptions
	{
		XMLOptionElementNodesOnly = 0x0001
	};

	class XMLDocument
	{
	public:
		XMLDocument(const std::string &filepath, int options = 0);
		~XMLDocument();

		XMLNode& GetRootNode() { return mRootNode; }

	private:
		XMLNode mRootNode;

		void ParseNodeTree(XMLNode &parentNode, rapidxml::xml_node<> *rapidxmlNode);
	};
};