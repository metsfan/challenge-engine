#include <Engine/Challenge.h>
#include <Engine/UI/Controls/HiddenView.h>

namespace challenge
{
	void HiddenView::ParseFromXML(XMLNode &node)
	{
		FormElement::ParseFromXML(node);

		mValue = node.GetAttributeString("value");
	}
}