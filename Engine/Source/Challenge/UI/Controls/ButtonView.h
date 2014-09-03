#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/FormElement.h>
#include <Challenge/UI/Controls/LabelView.h>

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
		virtual ~ButtonView() {}

		void SetState(ButtonState state) { mState = state; }
		ButtonState GetState() { return mState; }

		void SetTitleText(const std::string &text);
		void SetTitleColor(const Color &color);

		void SetValue(const std::string &value) { this->SetTitleText(value); }
		std::string GetValue() { return StringUtil::ToNarrow(mTitleLabel->GetText()); }

		virtual void SetBackgroundColor(const Color &color);

		virtual void Measure(const Size &parentSize);
		virtual void Update(int deltaMillis);

	protected:
		ButtonState mState;
		LabelView *mTitleLabel;

		virtual void ParseFromXML(XMLNode &node);

		
	};
};