#include <Engine/Challenge.h>
#include "OptionsView.h"

namespace challenge
{
	OptionsView::OptionsView(Frame frame) :
		MultiFormElement(frame),
		mMaxSelected(kInfinity)
	{
	}

	OptionsView::~OptionsView()
	{
	}

	void OptionsView::Update(int deltaMillis)
	{
		while(mSelectedItems.size() > mMaxSelected) {
			int index = mSelectedItems[mSelectedItems.size() - 1];
			mCheckboxes[index]->SetSelected(false);
			mSelectedItems.pop_back();
		}

		View::Update(deltaMillis);
	}

	void OptionsView::AddOption(const std::string &value, const std::string &text)
	{
		int index = mItems.size();
		real y = index * 30;
		CheckboxView *checkbox = new CheckboxView(Frame(0, y, 200, 30));
		checkbox->SetText(text);
		checkbox->AddMouseDownDelegate([this, index, checkbox](View *sender, const MouseEvent &e) {
			if(checkbox->IsSelected()) {
				if(mMaxSelected == 1) {
					if(mSelectedItems.size() > 0) {
						mCheckboxes[mSelectedItems[0]]->SetSelected(false);
						mSelectedItems.clear();
					}

					mSelectedItems.push_back(index);
				} else {
					if(mSelectedItems.size() < mMaxSelected) {
						mSelectedItems.push_back(index);
					} else {
						checkbox->SetSelected(false);
					}
				}
			} else {
				auto item = std::find(mSelectedItems.begin(), mSelectedItems.end(), index);
				if(item != mSelectedItems.end()) {
					mSelectedItems.erase(item);
				}
			}
			
		});
		this->AddInternalSubview(checkbox);
		mCheckboxes.push_back(checkbox);

		ListItem item;
		item.text = text;
		item.value = value;
		mItems.push_back(item);
	}

	void OptionsView::SetMaxSelected(int maxSelected)
	{
		mMaxSelected = maxSelected;

		while(mSelectedItems.size() > mMaxSelected) {
			mSelectedItems.pop_back();
		}
	}

	std::vector<std::string> OptionsView::GetSelectedValues()
	{
		std::vector<std::string> values;

		for(int index : mSelectedItems) {
			values.push_back(mItems[index].value);
		}

		return values;
	}

	void OptionsView::SetValue(int index, const std::string &value)
	{
		if(index < mSelectedItems.size()) {
			mItems[mSelectedItems[index]].value = value;
		}
	}

	std::string OptionsView::GetValue(int index)
	{
		if(index < mSelectedItems.size()) {
			return mItems[mSelectedItems[index]].value;
		}

		return std::string();
	}
};