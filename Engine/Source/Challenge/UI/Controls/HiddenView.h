#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/FormElement.h>

namespace challenge
{
	class HiddenView : public FormElement
	{
	public:
		HiddenView() :
			FormElement()
		{
		}

		virtual ~HiddenView()
		{
		}

		void SetVisible(bool visible) {
			FormElement::SetVisibility(ViewGone);
		}

		bool IsVisible() { return false; }

		void SetValue(const std::string &value) { mValue = value; }
		std::string GetValue() { return mValue; }

		void ParseFromXML(XMLNode &node);

	private:
		std::string mValue;
	};
};