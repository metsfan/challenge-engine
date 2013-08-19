#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/LabelView.h>
#include <Engine/UI/Controls/PanelView.h>

namespace challenge
{
	class CheckboxView : public View
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
	
	private:
		PanelView *mUncheckedImage;
		PanelView *mCheckedImage;
		LabelView *mTextLabel;
		bool mSelected;
	};
};