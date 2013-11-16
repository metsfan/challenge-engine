#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/LabelView.h>

namespace challenge
{
	class ButtonView;

	class FileSelectView : public FormElement
	{
	public:
		FileSelectView(Frame frame = Frame());
		~FileSelectView();

		const std::string& GetFilepath() { return mCurrentFileLabel->GetText(); }

		void SetValue(const std::string &value) { mCurrentFileLabel->SetText(value); }
		std::string GetValue() { return this->GetFilepath(); }

	private:
		LabelView *mCurrentFileLabel;
		ButtonView *mBrowseButton;
	};
}