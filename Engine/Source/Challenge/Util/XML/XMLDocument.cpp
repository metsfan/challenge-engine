#include <Challenge/Challenge.h>
#include <Challenge/Disk/File.h>
#include <Challenge/Util/XML/XMLDocument.h>

namespace challenge
{
	XMLDocument::XMLDocument(const std::string &filepath, int options)
	{
		File file(filepath);
		file.ReadData();
		this->LoadFile(&file, options);
	}

	XMLDocument::XMLDocument(File *file, int options)
	{
		this->LoadFile(file, options);
	}

	XMLDocument::~XMLDocument()
	{
	}

	void XMLDocument::LoadFile(File *file, int options)
	{
		TByteArray data = file->GetData();

		if(data.size()) {
			data.push_back('\0');
			rapidxml::xml_document<> doc;
			doc.parse<0>((char *)&data[0]);

			rapidxml::xml_node<> *root = doc.first_node(0);
			if(!root) {
				throw "Could not find root node";
			}

			mRootNode = XMLNode(root->name(), root->value());
			rapidxml::xml_attribute<> *attr = root->first_attribute(0);
			while(attr) {
				mRootNode.SetAttribute(std::string(attr->name()), std::string(attr->value()));

				attr = attr->next_attribute();
			}

			this->ParseNodeTree(mRootNode, root->first_node(0));
		}
	}

	void XMLDocument::ParseNodeTree(XMLNode &parentNode, rapidxml::xml_node<> *rapidxmlNode)
	{
		while(rapidxmlNode) {
			XMLNode node(rapidxmlNode->name(), rapidxmlNode->value());

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