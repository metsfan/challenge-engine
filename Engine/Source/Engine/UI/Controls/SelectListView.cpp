#include <Engine/Challenge.h>
#include "SelectListView.h"

namespace challenge
{
	static const int kButtonWidth = 20;
	static const int kItemHeight = 20;
	static const int kOptionsPanelMaxHeight = 160;
	static const Color kOptionHighlightColor(51, 153, 255, 255);
	static const Color kOptionBorderColor(127, 157, 185, 255);
	static const Color kOptionHighlightTextColor(255, 255, 255, 255);

	static const std::shared_ptr<Image> sDefaultSelectImage(new Image("C:/gamedev/dungeon-raider/DungeonRaider/Debug/select_list_arrow.png"));

	SelectListView::SelectListView(Frame frame) :
		FormElement(frame),
		mSelectedIndex(0),
		mDefaultOption(0),
		mOptionsPanel(new PanelView(Frame(0, 0, frame.size.width, 0))),
		mSelectedLabel(new LabelView(Frame(0, 0, frame.size.width - kButtonWidth, kItemHeight))),
		mSelectButton(new ButtonView(Frame(frame.size.width - kButtonWidth, 0, kButtonWidth, kItemHeight)))
	{
		this->AddInternalSubview(mSelectedLabel);
		this->AddInternalSubview(mSelectButton);
		//this->AddInternalSubview(mOptionsPanel);
		mOptionsPanel->SetVisible(false);
		mOptionsPanel->SetScrollable(true);
		mOptionsPanel->SetBackgroundColor(Color::White());
		mOptionsPanel->SetBorderWidth(1);
		mOptionsPanel->SetBorderColor(kOptionBorderColor);

		mOptionsPanelPosition = Point(0, kItemHeight);

		auto showSelectPanel = [this](View *sender, const MouseEvent &e) {
			auto window = this->GetWindow();
			if (window) {
				if (mOptionsPanel->IsVisible()) {
					mOptionsPanel->SetVisible(false);
					mOptionsPanel->RemoveFromSuperview();
				}
				else {
					mOptionsPanel->SetPosition(this->GetPositionInView(mOptionsPanelPosition, window));
					mOptionsPanel->SetFocused(true);
					mOptionsPanel->SetVisible(true);
					window->AddSubview(mOptionsPanel);
				}
			}
		};
			
		mSelectedLabel->AddMouseEvent(MouseEventMouseDown, showSelectPanel);
		mSelectButton->AddMouseEvent(MouseEventMouseDown, showSelectPanel);
		mSelectButton->SetBackgroundImage(sDefaultSelectImage);

		mSelectedLabel->SetBackgroundColor(Color::White());

		this->SetBorderColor(kOptionBorderColor);
		this->SetBorderWidth(1);
	}

	SelectListView::~SelectListView()
	{
		delete mOptionsPanel;
		delete mSelectedLabel;
		delete mSelectButton;
	}

	void SelectListView::SetFrame(const Frame &frame)
	{
		FormElement::SetFrame(frame);

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
		itemButton->AddMouseEvent(MouseEventMouseUp, [this](View *sender, const MouseEvent &e) {
			this->SetSelectedIndex(sender->GetTag());
			mOptionsPanel->SetVisible(false);
			mOptionsPanel->RemoveFromSuperview();
		});

		itemButton->AddMouseEvent(MouseEventMouseEnter, [this, itemButton](View *sender, const MouseEvent &e) {
			itemButton->SetBackgroundColor(kOptionHighlightColor);
			itemButton->SetTitleColor(Color::White());
		});

		itemButton->AddMouseEvent(MouseEventMouseLeave, [this, itemButton](View *sender, const MouseEvent &e) {
			itemButton->SetBackgroundColor(Color::White());
			itemButton->SetTitleColor(Color::Black());
		});

		mButtons.push_back(itemButton);
		mOptionsPanel->AddSubview(itemButton);

		ListItem item;
		item.text = text;
		item.value = value;

		mItems.push_back(item);

		if (mDefaultOption == index) {
			this->SetSelectedIndex(index);
		}

		int height = mOptionsPanel->GetHeight();
		if (height < kOptionsPanelMaxHeight) {
			mOptionsPanel->SetHeight(kItemHeight * mItems.size());
		}
		else {
			mOptionsPanel->SetHeight(kOptionsPanelMaxHeight);
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

		for (SelectListDelegate &nDelegate : mValueChangedDelegates) {
			nDelegate(this);
		}
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
		FormElement::Update(deltaMillis);
	}

	void SelectListView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		FormElement::Render(device, state, parentFrame);
	}

	void SelectListView::ParseFromXML(XMLNode &node)
	{
		FormElement::ParseFromXML(node);

		TXMLNodeList &options = node.GetChildrenByName("Option");
		for(XMLNode &optionNode : options) {
			this->AddOption(optionNode.GetAttributeString("value"), optionNode.GetAttributeString("text"));
		}
	}
};