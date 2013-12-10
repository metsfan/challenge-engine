#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/FormElement.h>
#include <Challenge/UI/Controls/LabelView.h>
#include <Challenge/UI/Controls/ButtonView.h>
#include <Challenge/UI/Controls/PanelView.h>

namespace challenge
{
	class SelectListView;

	typedef std::function<void(SelectListView *)> SelectListDelegate;

	class SelectListView : public FormElement
	{
	public:
		SelectListView(Frame frame = Frame());
		virtual ~SelectListView();

		virtual void SetFrame(const Frame &frame);

		void AddOption(const std::string &value, const std::string &text);
		void SetDefaultOption(int index);
		void SetSelectedIndex(int index);
		int GetSelectedIndex() { return mSelectedIndex; }
		const ListItem& GetSelectedItem() { return mItems[mSelectedIndex]; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetValue(const std::string &value);
		std::string GetValue() { 
			if (mItems.size() > mSelectedIndex) {
				return mItems[mSelectedIndex].value;
			}

			return "";
		}

		void AddValueChangedDelegate(SelectListDelegate changeDelegate)
		{
			mValueChangedDelegates.push_back(changeDelegate);
		}

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		std::vector<ListItem> mItems;
		std::vector<ButtonView *> mButtons;
		PanelView *mOptionsPanel;
		LabelView *mSelectedLabel;
		ButtonView *mSelectButton;
		Point mOptionsPanelPosition;
		ButtonView *mActiveItem;
		std::vector<SelectListDelegate> mValueChangedDelegates;
		int mSelectedIndex;
		int mDefaultOption;
	};
};