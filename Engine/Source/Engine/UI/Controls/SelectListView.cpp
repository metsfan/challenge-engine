#include <Engine/Challenge.h>
#include "SelectListView.h"

namespace challenge
{
	static const int kButtonWidth = 18;
	static const int kItemHeight = 20;
	static const int kOptionsPanelHeight = 150;

	static const std::shared_ptr<Image> sDefaultSelectImage(new Image("C:/gamedev/dungeon-raider/DungeonRaider/Debug/select_list_arrow.png"));

	SelectListView::SelectListView(Frame frame) :
		FormElement(frame),
		mSelectedIndex(0),
		mDefaultOption(0),
		mOptionsPanel(new PanelView(Frame(0, kItemHeight, frame.size.width, kOptionsPanelHeight))),
		mSelectedLabel(new LabelView(Frame(0, 0, frame.size.width - kButtonWidth, kItemHeight))),
		mSelectButton(new ButtonView(Frame(frame.size.width - kButtonWidth, 0, kButtonWidth, kItemHeight)))
	{
		this->AddInternalSubview(mSelectedLabel);
		this->AddInternalSubview(mSelectButton);
		this->AddInternalSubview(mOptionsPanel);
		mOptionsPanel->SetVisible(false);
		mOptionsPanel->SetScrollable(true);

		mSelectButton->AddMouseDownDelegate([this](View *sender, const MouseEvent &e) {
			mOptionsPanel->SetVisible(!mOptionsPanel->IsVisible()); 
			if(mOptionsPanel->IsVisible()) {
				mOptionsPanel->SetFocused(true);
			}
		});
		mSelectButton->SetBackgroundImage(sDefaultSelectImage);

		mSelectedLabel->SetBackgroundColor(Color(255, 255, 255, 255));
	}

	SelectListView::~SelectListView()
	{
		delete mOptionsPanel;
		delete mSelectedLabel;
		delete mSelectButton;
	}

	void SelectListView::SetFrame(const Frame &frame)
	{
		View::SetFrame(frame);

		mOptionsPanel->SetWidth(frame.size.width);
		mSelectedLabel->SetWidth(frame.size.width - kButtonWidth);
		mSelectButton->SetX(frame.size.width - kButtonWidth);
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

	void SelectListView::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);

		TXMLNodeList &options = node.GetChildrenByName("Option");
		for(XMLNode &optionNode : options) {
			this->AddOption(optionNode.GetAttributeString("value"), optionNode.GetAttributeString("text"));
		}
	}
};