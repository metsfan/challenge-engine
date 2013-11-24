#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FileSelectView.h>
#include <Engine/UI/Controls/ButtonView.h>
#include <Engine/UI/Util/FileDialog.h>
#include <Engine/Util/StringUtil.h>

#include <locale>

namespace challenge
{
	static const int kBrowseButtonWidth = 50;

	FileSelectView::FileSelectView(Frame frame) :
		FormElement(frame),
		mCurrentFileLabel(new TextFieldView(Frame(0, 0, frame.size.width - kBrowseButtonWidth, frame.size.height))),
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
			std::vector<std::wstring> files = FileDialog::OpenFileDialog(mCurrentDialogOptions);

			if (files.size()) {
				mCurrentFileLabel->SetText(StringUtil::ConvertString<std::wstring, std::string>(files[0]));
				mCurrentFileLabel->ResetCursor();
			}
		});
	}

	FileSelectView::~FileSelectView()
	{
	}

	void FileSelectView::SetFileExtensions(const std::wstring &extensions)
	{
		mCurrentDialogOptions.Filters.clear();

		std::vector<std::wstring> pairs = StringUtil::SplitString<std::wstring>(extensions, L",");
		for (std::wstring &pair : pairs) {
			std::vector<std::wstring> pairArray = StringUtil::SplitString<std::wstring>(pair, L"|");
			if (pairArray.size() == 1) {
				mCurrentDialogOptions.Filters.push_back(DialogFilter(L"", pairArray[0]));
			}
			else if (pairArray.size() > 1) {
				mCurrentDialogOptions.Filters.push_back(DialogFilter(pairArray[1], pairArray[0]));
			}
		}
	}

	void FileSelectView::SetDefaultDirectory(const std::wstring &directory)
	{
		mCurrentDialogOptions.DefaultDirectory = directory;
	}
};