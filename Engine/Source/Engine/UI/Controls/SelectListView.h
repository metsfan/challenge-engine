#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/LabelView.h>
#include <Engine/UI/Controls/ButtonView.h>
#include <Engine/UI/Controls/PanelView.h>

namespace challenge
{
	class SelectListView : public FormElement
	{
	public:
		SelectListView(Frame frame = Frame());
		~SelectListView();

		virtual void SetFrame(const Frame &frame);

		void AddOption(const std::string &value, const std::string &text);
		void SetDefaultOption(int index);
		void SetSelectedIndex(int index);
		int GetSelectedIndex() { return mSelectedIndex; }
		const ListItem& GetSelectedItem() { return mItems[mSelectedIndex]; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetValue(const std::string &value);
		std::string GetValue() { return mItems[mSelectedIndex].value; }

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		std::vector<ListItem> mItems;
		std::vector<ButtonView *> mButtons;
		PanelView *mOptionsPanel;
		LabelView *mSelectedLabel;
		ButtonView *mSelectButton;
		Point mOptionsPanelPosition;
		int mSelectedIndex;
		int mDefaultOption;
	};
};