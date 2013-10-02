#include <Engine/Challenge.h>
#include "SelectListView.h"

namespace challenge
{
	static const int kItemHeight = 30;
	static const int kOptionsPanelHeight = 150;

	SelectListView::SelectListView(Frame frame) :
		FormElement(frame),
		mSelectedIndex(0),
		mDefaultOption(0),
		mOptionsPanel(new PanelView(Frame(0, kItemHeight, frame.size.width, kOptionsPanelHeight))),
		mSelectedLabel(new LabelView(Frame(0, 0, frame.size.width - 50, kItemHeight))),
		mSelectButton(new ButtonView(Frame(frame.size.width - 30, 0, 30, kItemHeight)))
	{
		this->AddSubview(mSelectedLabel);
		this->AddSubview(mSelectButton);
		this->AddSubview(mOptionsPanel);
		mOptionsPanel->SetVisible(false);
		mOptionsPanel->SetScrollable(true);

		mSelectButton->AddMouseDownDelegate([this](View *sender, const MouseEvent &e) {
			mOptionsPanel->SetVisible(!mOptionsPanel->IsVisible()); 
			if(mOptionsPanel->IsVisible()) {
				mOptionsPanel->SetFocused(true);
			}
		});
		mSelectButton->SetBackgroundColor(glm::vec4(0, 0, 0, 255));
	}

	SelectListView::~SelectListView()
	{
		delete mOptionsPanel;
		delete mSelectedLabel;
		delete mSelectButton;
	}

	void SelectListView::AddOption(const std::string &value, const std::string &text)
	{
		const Frame &frame = this->GetFrame();
		int index = mItems.size();
		
		ButtonView *itemButton = new ButtonView(Frame(0, index * kItemHeight, frame.size.width, kItemHeight));
		itemButton->SetTitleText(text);
		itemButton->SetTag(index);
		itemButton->AddMouseUpDelegate([this](View *sender, const MouseEvent &e) {
			this->SetSelectedIndex(sender->GetTag());
			this->mOptionsPanel->SetVisible(false);
		});

		mButtons.push_back(itemButton);
		mOptionsPanel->AddSubview(itemButton);

		ListItem item;
		item.text = text;
		item.value = value;

		mItems.push_back(item);

		if(mDefaultOption == index) {
			this->SetSelectedIndex(index);
		}
	}

	void SelectListView::SetDefaultOption(int index)
	{
		mDefaultOption = index;
	}

	void SelectListView::SetSelectedIndex(int index)
	{
		mSelectedIndex = index;

		const ListItem &item = mItems[index];
		mSelectedLabel->SetText(item.text);
	}

	void SelectListView::SetValue(const std::string &value)
	{
		for(int i = 0; i < mItems.size(); i++) {
			if(mItems[i].value == value) {
				this->SetSelectedIndex(i);
			}
		}
	}

	void SelectListView::Update(int deltaMillis)
	{
		View::Update(deltaMillis);
	}

	void SelectListView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		View::Render(device, state, parentFrame);
	}
};