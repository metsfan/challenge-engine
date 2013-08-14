#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>
#include <Engine/UI/Controls/LabelView.h>

namespace challenge
{
	typedef enum {
		ButtonStateDefault,
		ButtonStateHighlighted,
		ButtonStateSelected,
		ButtonStateDisabled
	} ButtonState;

	class ButtonView : public View
	{
	private:
		void Initialize();

	public:
		ButtonView(Frame frame = Frame());

		void SetState(ButtonState state) { mState = state; }
		ButtonState GetState() { return mState; }

		void SetTitleText(const std::string &text);

	protected:
		ButtonState mState;
		LabelView *mTitleLabel;
	};
};