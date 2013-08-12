#include <Engine/Challenge.h>
#include <Engine/UI/Controls/ButtonView.h>

namespace challenge
{
	ButtonView::ButtonView(void) : View()
	{
		mState = ButtonStateDefault;
		mTitleLabel = new LabelView();
		mTitleLabel->SetTextColor(Color(0,0,0,1));
		this->AddSubview(mTitleLabel);
	}

	ButtonView::ButtonView(Frame frame) : View(frame)
	{
		mState = ButtonStateDefault;
		mTitleLabel = new LabelView();
		mTitleLabel->SetFrame(frame);
		mTitleLabel->SetTextColor(Color(0,0,0,1));
		this->AddSubview(mTitleLabel);
	}

	void ButtonView::SetTitleText(std::string text)
	{
		if (mTitleLabel) {
			mTitleLabel->SetText(text, false);
		}
	}

};

/*void ButtonView::OnRender(GLSLProgram *program)
{
	View::OnRender(program);
}*/