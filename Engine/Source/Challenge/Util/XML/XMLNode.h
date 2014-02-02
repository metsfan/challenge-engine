#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Util/XML/XMLAttribute.h>

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
		TXMLNodeList GetChildrenByName(const std::string &name);
		XMLNode& GetFirstChild(const std::string &name);
		XMLNode& GetChild(int index);

		std::string GetValue() { return mValue; }

		void AddChild(XMLNode &node) { mChildren.push_back(node); }

		std::string GetAttributeString(const std::string &name);
		short GetAttributeShort(const std::string &name);
		int GetAttributeInt(const std::string &name);
		float GetAttributeFloat(const std::string &name);
		double GetAttributeDouble(const std::string &name);

		void SetAttribute(const std::string &name, std::string value);
		void SetAttribute(const std::string &name, short value);
		void SetAttribute(const std::string &name, int value);
		void SetAttribute(const std::string &name, float value);
		void SetAttribute(const std::string &name, double value);

		bool HasAttribute(const std::string &name) { return mAttributes.count(name); }

		const TXMLAttributeMap& GetAttributes() { return mAttributes; }

	private:
		std::string mName;
		std::string mValue;
		TXMLNodeList mChildren;
		TXMLAttributeMap mAttributes;
	};
};