#pragma once

#include <Engine/Challenge.h>
#include <Engine/Util/XML/XMLAttribute.h>

namespace challenge
{
	class XMLNode;

	typedef std::vector<XMLNode> TXMLNodeList;
	typedef std::map<std::string, XMLAttribute> TXMLAttributeMap;

	class XMLNode
	{
	public:
		XMLNode();
		XMLNode(const std::string &name, const std::string &value);
		~XMLNode();

		const std::string& GetName() { return mName; }
		int GetNumChildren() { return mChildren.size(); }
		TXMLNodeList GetChildren() { return mChildren; }
		TXMLNodeList GetChildrenByName(std::string name);
		XMLNode& GetFirstChild(std::string name);
		XMLNode& GetChild(int index);

		std::string GetValue() { return mValue; }

		void AddChild(XMLNode &node) { mChildren.push_back(node); }

		std::string GetAttributeString(std::string name);
		short GetAttributeShort(std::string name);
		int GetAttributeInt(std::string name);
		float GetAttributeFloat(std::string name);
		double GetAttributeDouble(std::string name);

		void SetAttribute(std::string name, std::string value);
		void SetAttribute(std::string name, short value);
		void SetAttribute(std::string name, int value);
		void SetAttribute(std::string name, float value);
		void SetAttribute(std::string name, double value);

	private:
		std::string mName;
		std::string mValue;
		TXMLNodeList mChildren;
		TXMLAttributeMap mAttributes;
	};
};