#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>

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