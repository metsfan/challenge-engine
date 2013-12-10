#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/FormElement.h>

namespace challenge
{
	void FormElement::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);

		mName = node.GetAttributeString("name");
	}

	void MultiFormElement::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);

		mName = node.GetAttributeString("name");
	}
}