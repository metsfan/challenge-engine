#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/FormElement.h>
#include <Challenge/UI/Controls/TextFieldView.h>

namespace challenge
{
	class ButtonView;

	class FileSelectView : public FormElement
	{
	public:
		FileSelectView(Frame frame = Frame());
		virtual ~FileSelectView();

		const std::string& GetFilepath() { return mCurrentFileLabel->GetText(); }

		void SetValue(const std::string &value) { mCurrentFileLabel->SetText(value); }
		std::string GetValue() { return this->GetFilepath(); }

		void SetFileExtensions(const std::wstring &extensions);
		void SetDefaultDirectory(const std::wstring &directory);

	private:
		TextFieldView *mCurrentFileLabel;
		ButtonView *mBrowseButton;

		OPEN_FILE_DIALOG_DESC mCurrentDialogOptions;
	};
}