#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>

namespace challenge
{
	class HiddenView : public FormElement
	{
	public:
		HiddenView() :
			FormElement()
		{
		}

		~HiddenView()
		{
		}

		void SetVisible(bool visible) {
			FormElement::SetVisible(false);
		}

		bool IsVisible() { return false; }

		void SetValue(const std::string &value) { mValue = value; }
		std::string GetValue() { return mValue; }

		void ParseFromXML(XMLNode &node);

	private:
		std::string mValue;
	};
};