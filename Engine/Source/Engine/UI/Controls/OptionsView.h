#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/CheckboxView.h>

namespace challenge
{
	class OptionsView : public MultiFormElement
	{
	public:
		OptionsView(Frame frame = Frame());
		virtual ~OptionsView();

		void Update(int deltaMillis);

		void AddOption(const std::string &value, const std::string &text);
		void SetMaxSelected(int maxSelected);
		std::vector<std::string> GetSelectedValues();

		int GetNumValues() { return mSelectedItems.size(); }
		void SetValue(int index, const std::string &value);
		std::string GetValue(int index);

	private:
		std::vector<CheckboxView *> mCheckboxes;
		std::vector<ListItem> mItems;
		std::vector<int> mSelectedItems;
		int mMaxSelected;
	};
};