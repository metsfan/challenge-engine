#include <Challenge/Challenge.h>
#include <Challenge/Util/XML/XMLNode.h>

namespace challenge
{
	XMLNode::XMLNode()
	{
	}

	XMLNode::XMLNode(const std::string &name, const std::string &value) :
		mName(name),
		mValue(value)
	{
	}

	XMLNode::~XMLNode()
	{
	}

	TXMLNodeList XMLNode::GetChildrenByName(const std::string &name)
	{
		TXMLNodeList nodes;

		for(XMLNode &node : mChildren) {
			if(node.mName == name) {
				nodes.push_back(node);
			}
		}

		return nodes;
	}

	XMLNode& XMLNode::GetFirstChild(const std::string &name)
	{
		for(XMLNode &node : mChildren) {
			if(node.mName == name) {
				return node;
			}
		}
	}

	XMLNode& XMLNode::GetChild(int index)
	{
		if(mChildren.size() >= index) {
			throw "Index out of bounds";
		}

		return mChildren[index];
	}

	std::string XMLNode::GetAttributeString(const std::string &name)
	{
		if(mAttributes.count(name)) {
			return mAttributes[name].GetValue();
		}

		return "";
	}

	bool XMLNode::GetAttributeBoolean(const std::string &name)
	{
		std::string strval = this->GetAttributeString(name);
		if (strval == "true") {
			return true;
		}

		return false;
	}

	short XMLNode::GetAttributeShort(const std::string &name)
	{
		std::string strval = this->GetAttributeString(name);
		if(strval.length() > 0) {
			return (short)atoi(strval.c_str());
		}
		return 0;
	}

	int XMLNode::GetAttributeInt(const std::string &name)
	{
		std::string strval = this->GetAttributeString(name);
		if(strval.length() > 0) {
			return atoi(strval.c_str());
		}
		return 0;
	}

	float XMLNode::GetAttributeFloat(const std::string &name)
	{
		std::string strval = this->GetAttributeString(name);
		if(strval.length() > 0) {
			return (float)atof(strval.c_str());
		}
		return 0;
	}

	double XMLNode::GetAttributeDouble(const std::string &name)
	{
		std::string strval = this->GetAttributeString(name);
		if(strval.length() > 0) {
			return atof(strval.c_str());
		}
		return 0;
	}

	void XMLNode::SetAttribute(const std::string &name, std::string value)
	{
		if(mAttributes.count(name)) {
			return mAttributes[name].SetValue(value);
		} else {
			mAttributes.insert(
				std::pair<std::string, XMLAttribute>(name, XMLAttribute(name, value))
			);
		}
	}

	void XMLNode::SetAttribute(const std::string &name, short value)
	{
		std::stringstream ss;
		ss << value;
		this->SetAttribute(name, ss.str());
	}

	void XMLNode::SetAttribute(const std::string &name, int value)
	{
		std::stringstream ss;
		ss << value;
		this->SetAttribute(name, ss.str());
	}

	void XMLNode::SetAttribute(const std::string &name, float value)
	{
		std::stringstream ss;
		ss << value;
		this->SetAttribute(name, ss.str());
	}

	void XMLNode::SetAttribute(const std::string &name, double value)
	{
		std::stringstream ss;
		ss << value;
		this->SetAttribute(name, ss.str());
	}
};