#include <Engine/Challenge.h>
#include <Engine/UI/Controls/ButtonView.h>

namespace challenge
{
	ButtonView::ButtonView(Frame frame) : View(frame)
	{
		mState = ButtonStateDefault;
		mTitleLabel = new LabelView();
		mTitleLabel->SetFrame(Frame(0, 0, frame.size.width, frame.size.height));
		mTitleLabel->SetTextColor(Color(0,0,0,1));
		this->AddSubview(mTitleLabel);
	}

	void ButtonView::SetTitleText(const std::string &text)
	{
		if (mTitleLabel) {
			mTitleLabel->SetText(text);
		}
	}

};

/*void ButtonView::OnRender(GLSLProgram *program)
{
	View::OnRender(program);
}*/