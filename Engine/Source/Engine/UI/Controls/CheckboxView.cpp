#include <Engine/Challenge.h>
#include "CheckboxView.h"

namespace challenge
{
	static const std::shared_ptr<Image> sDefaultCheckedImage(new Image("C:/gamedev/dungeon-raider/DungeonRaider/Debug/checkbox_checked.png"));
	static const std::shared_ptr<Image> sDefaultUncheckedImage(new Image("C:/gamedev/dungeon-raider/DungeonRaider/Debug/checkbox_unchecked.png"));
	static const int kCheckboxBuffer = 2;

	CheckboxView::CheckboxView(Frame frame) :
		FormElement(frame),
		mCheckedImage(new ButtonView()),
		mUncheckedImage(new ButtonView()),
		mTextLabel(new LabelView()),
		mSelected(false)
	{
		mCheckedImage->SetBackgroundImage(sDefaultCheckedImage);
		mCheckedImage->SetVisible(false);
		mCheckedImage->SetSize(sDefaultCheckedImage->GetSize());
		this->AddInternalSubview(mCheckedImage);

		mUncheckedImage->SetBackgroundImage(sDefaultUncheckedImage);
		mUncheckedImage->SetSize(sDefaultUncheckedImage->GetSize());
		this->AddInternalSubview(mUncheckedImage);

		mCheckedImage->AddMouseDownDelegate([this](View *sender, const MouseEvent &e) {
			this->SetSelected(false);
		});

		mUncheckedImage->AddMouseDownDelegate([this](View *sender, const MouseEvent &e) {
			this->SetSelected(true);
		});

		this->AddInternalSubview(mTextLabel);
	}

	CheckboxView::~CheckboxView()
	{
	}

	void CheckboxView::SetText(const std::string &text)
	{
		mTextLabel->SetText(text);
	}

	void CheckboxView::SetSelected(bool selected)
	{
		mSelected = selected;

		if(mSelected) {
			mCheckedImage->SetVisible(true);
			mUncheckedImage->SetVisible(false);
		} else {
			mCheckedImage->SetVisible(false);
			mUncheckedImage->SetVisible(true);
		}
	}

	void CheckboxView::SetUncheckedImage(std::shared_ptr<Image> image)
	{
		if(image) {
			mUncheckedImage->SetBackgroundImage(image);
		}
	}

	void CheckboxView::SetCheckedImage(std::shared_ptr<Image> image)
	{
		if(image) {
			mCheckedImage->SetBackgroundImage(image);
		}
	}

	void CheckboxView::Update(int deltaMillis)
	{
		mTextLabel->SetX(mCheckedImage->GetWidth() + kCheckboxBuffer * 2);

		real checkboxY = (this->GetHeight() - mCheckedImage->GetHeight()) / 2;
		mCheckedImage->SetPosition(kCheckboxBuffer, checkboxY);
		mUncheckedImage->SetPosition(kCheckboxBuffer, checkboxY);

		View::Update(deltaMillis);
	}
};