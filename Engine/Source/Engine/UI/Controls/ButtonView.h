#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/LabelView.h>

namespace challenge
{
	typedef enum {
		ButtonStateDefault,
		ButtonStateHighlighted,
		ButtonStateSelected,
		ButtonStateDisabled
	} ButtonState;
	 
	class ButtonView : public FormElement
	{
	private:
		void Initialize();

	public:
		ButtonView(Frame frame = Frame());

		void SetState(ButtonState state) { mState = state; }
		ButtonState GetState() { return mState; }

		void SetTitleText(const std::string &text);

		void SetValue(const std::string &value) { this->SetTitleText(value); }
		std::string GetValue() { return mTitleLabel->GetText(); }

	protected:
		ButtonState mState;
		LabelView *mTitleLabel;

		virtual void ParseFromXML(XMLNode &node);
	};
};