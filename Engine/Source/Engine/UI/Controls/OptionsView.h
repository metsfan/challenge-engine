#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/CheckboxView.h>

namespace challenge
{
	class OptionsView : public View
	{
	public:
		OptionsView(Frame frame = Frame());
		~OptionsView();

		void Update(int deltaMillis);

		void AddOption(const std::string &value, const std::string &text);
		void SetMaxSelected(int maxSelected);
		std::vector<std::string> GetSelectedValues();

	private:
		std::vector<CheckboxView *> mCheckboxes;
		std::vector<ListItem> mItems;
		std::vector<int> mSelectedItems;
		int mMaxSelected;
	};
};