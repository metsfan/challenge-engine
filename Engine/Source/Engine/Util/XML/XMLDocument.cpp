#include <Engine/Challenge.h>
#include <Engine/Util/XML/XMLDocument.h>
#include <Engine/Util/Util.h>

namespace challenge
{
	XMLDocument::XMLDocument(const std::string &filepath, int options)
	{
		std::string data = Util::ReadContentsOfFile(filepath);

		rapidxml::xml_document<> doc;
		doc.parse<0>(&data[0]);

		rapidxml::xml_node<> *root = doc.first_node(0);
		if(!root) {
			throw "Could not find root node";
		}

		mRootNode = XMLNode(root->name());
		this->ParseNodeTree(mRootNode, root->first_node(0));
	}

	XMLDocument::~XMLDocument()
	{
	}

	void XMLDocument::ParseNodeTree(XMLNode &parentNode, rapidxml::xml_node<> *rapidxmlNode)
	{
		while(rapidxmlNode) {
			XMLNode node(rapidxmlNode->name());

			rapidxml::xml_attribute<> *attr = rapidxmlNode->first_attribute(0);
			while(attr) {
				node.SetAttribute(std::string(attr->name()), std::string(attr->value()));

				attr = attr->next_attribute();
			}

			this->ParseNodeTree(node, rapidxmlNode->first_node(0));

			parentNode.AddChild(node);

			rapidxmlNode = rapidxmlNode->next_sibling();
		}
	}
};