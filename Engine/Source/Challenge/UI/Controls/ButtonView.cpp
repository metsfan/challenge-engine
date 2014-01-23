#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/ButtonView.h>

namespace challenge
{
	ButtonView::ButtonView(Frame frame) : 
		FormElement(frame)
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

	void ButtonView::SetBackgroundColor(const Color &color)
	{
		FormElement::SetBackgroundColor(color);

		mTitleLabel->SetBackgroundColor(color);
	}


	void ButtonView::ParseFromXML(XMLNode &node)
	{
		FormElement::ParseFromXML(node);

		this->SetTitleText(node.GetAttributeString("text"));
	}

	void ButtonView::SetTitleColor(const Color &color)
	{
		mTitleLabel->SetTextColor(color);
	}
};

/*void ButtonView::OnRender(GLSLProgram *program)
{
	View::OnRender(program);
}*/