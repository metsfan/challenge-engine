#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/LabelView.h>
#include <Engine/UI/Controls/ButtonView.h>

namespace challenge
{
	class CheckboxView : public FormElement
	{
	public:
		CheckboxView(Frame frame = Frame());
		~CheckboxView();

		virtual void Update(int deltaMillis);

		void SetText(const std::string &text);
		void SetSelected(bool selected);
		void SetUncheckedImage(std::shared_ptr<Image> image);
		void SetCheckedImage(std::shared_ptr<Image> image);

		bool IsSelected() { return mSelected; }

		void SetValue(const std::string &value) { this->SetSelected(value == "1"); }
		std::string GetValue() { return mSelected ? "1" : "0"; }
	
	private:
		ButtonView *mUncheckedImage;
		ButtonView *mCheckedImage;
		LabelView *mTextLabel;
		bool mSelected;
	};
};