#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/HiddenView.h>

namespace challenge
{
	void HiddenView::ParseFromXML(XMLNode &node)
	{
		FormElement::ParseFromXML(node);

		mValue = node.GetAttributeString("value");
	}
}