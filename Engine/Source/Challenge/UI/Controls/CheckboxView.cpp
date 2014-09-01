#include <Challenge/Challenge.h>
#include "CheckboxView.h"

namespace challenge
{
	static std::shared_ptr<Image> sDefaultCheckedImage = NULL;
	static std::shared_ptr<Image> sDefaultUncheckedImage = NULL;
	static const int kCheckboxBuffer = 2;

	CheckboxView::CheckboxView(Frame frame) :
		FormElement(frame),
		mCheckedImage(new ButtonView()),
		mUncheckedImage(new ButtonView()),
		mTextLabel(new LabelView()),
		mSelected(false)
	{
		if (!sDefaultCheckedImage) {
			Asset imageAsset(L"checkbox_checked.png");
			if (imageAsset.ReadData()) {
				sDefaultCheckedImage = std::shared_ptr<Image>(new Image(&imageAsset));
			}
		}

		if (!sDefaultUncheckedImage) {
			Asset imageAsset(L"uncheckbox_checked.png");
			if (imageAsset.ReadData()) {
				sDefaultCheckedImage = std::shared_ptr<Image>(new Image(&imageAsset));
			}
		}

		mCheckedImage->SetBackgroundImage(sDefaultCheckedImage);
		mCheckedImage->SetVisibility(ViewGone);
		mCheckedImage->SetSize(sDefaultCheckedImage->GetSize());
		this->AddInternalSubview(mCheckedImage);

		mUncheckedImage->SetBackgroundImage(sDefaultUncheckedImage);
		mUncheckedImage->SetSize(sDefaultUncheckedImage->GetSize());
		this->AddInternalSubview(mUncheckedImage);

		mCheckedImage->AddMouseEvent(MouseEventMouseDown, [this](View *sender, const MouseEvent &e) {
			this->SetSelected(false);
		});

		mUncheckedImage->AddMouseEvent(MouseEventMouseDown, [this](View *sender, const MouseEvent &e) {
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
			mCheckedImage->SetVisibility(ViewVisible);
			mUncheckedImage->SetVisibility(ViewVisible);
		} else {
			mCheckedImage->SetVisibility(ViewGone);
			mUncheckedImage->SetVisibility(ViewGone);
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

		FormElement::Update(deltaMillis);
	}
};