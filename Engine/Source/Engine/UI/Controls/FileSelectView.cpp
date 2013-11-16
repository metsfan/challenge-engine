#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FileSelectView.h>
#include <Engine/UI/Controls/ButtonView.h>

namespace challenge
{
	static const int kBrowseButtonWidth = 50;

	FileSelectView::FileSelectView(Frame frame) :
		FormElement(frame),
		mCurrentFileLabel(new LabelView(Frame(0, 0, frame.size.width - kBrowseButtonWidth, frame.size.height))),
		mBrowseButton(new ButtonView(Frame(mCurrentFileLabel->GetWidth() + 1, 0, kBrowseButtonWidth - 1, frame.size.height)))
	{
		this->AddInternalSubview(mCurrentFileLabel);
		this->AddInternalSubview(mBrowseButton);

		mCurrentFileLabel->SetBorderColor(Color::Black());
		mCurrentFileLabel->SetBorderWidth(1);
		mCurrentFileLabel->SetBackgroundColor(Color::White());

		mBrowseButton->SetTitleText("Browse");
		mBrowseButton->SetBackgroundColor(Color(220, 220, 220, 255));
		mBrowseButton->AddMouseEvent(MouseEventMouseDown, [this](View *sender, const MouseEvent &e) {
			this->GetWindow()->ShowNativeFileDialog(NULL);
		});
	}

	FileSelectView::~FileSelectView()
	{
	}
};