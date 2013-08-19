#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/LabelView.h>
#include <Engine/UI/Controls/ButtonView.h>
#include <Engine/UI/Controls/PanelView.h>

namespace challenge
{
	class SelectListView : public View
	{
	public:
		SelectListView(Frame frame = Frame());
		~SelectListView();

		void AddOption(const std::string &value, const std::string &text);
		void SetDefaultOption(int index);
		void SetSelectedIndex(int index);
		int GetSelectedIndex() { return mSelectedIndex; }
		const ListItem& GetSelectedItem() { return mItems[mSelectedIndex]; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

	private:
		std::vector<ListItem> mItems;
		std::vector<ButtonView *> mButtons;
		PanelView *mOptionsPanel;
		LabelView *mSelectedLabel;
		ButtonView *mSelectButton;
		int mSelectedIndex;
		int mDefaultOption;
	};
};