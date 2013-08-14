#include <Engine/Challenge.h>
#include "SelectListView.h"

namespace challenge
{
	static const int kItemHeight = 30;
	static const int kOptionsPanelHeight = 150;

	SelectListView::SelectListView(Frame frame) :
		View(frame),
		mSelectedIndex(0),
		mDefaultOption(0),
		mOptionsPanel(new PanelView(Frame(0, kItemHeight, frame.size.width, kOptionsPanelHeight))),
		mSelectedLabel(new LabelView(Frame(0, 0, frame.size.width - 50, kItemHeight))),
		mSelectButton(new ButtonView(Frame(frame.size.width - 50, 0, 50, kItemHeight)))
	{
		this->AddSubview(mSelectedLabel);
		this->AddSubview(mSelectButton);
		this->AddSubview(mOptionsPanel);
		//mOptionsPanel->SetVisible(false);

		mSelectButton->AddMouseUpDelegate([this](View *sender, const MouseEvent &e) {

		});
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

	void SelectListView::Update(int deltaMillis)
	{
		View::Update(deltaMillis);
	}

	void SelectListView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		View::Render(device, state, parentFrame);
	}
};