#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>
#include <Challenge/UI/ViewManager.h>
#include <Challenge/Util/Image.h>
//#include <Challenge/Util/TextureAtlas.h>
#include <Challenge/Renderer/Texture/Texture2DDX11.h>
#include <Challenge/GameApplication.h>
#include <Challenge/UI/Window.h>
#include <Challenge/UI/ViewXMLParser.h>
#include <Challenge/Input/InputManager.h>

namespace challenge
{
	std::map<std::string, TViewCreatorFunction> View::sViewCreatorRegistry;

	View::View(const Frame &frame) :
		mFrame(frame),
		mAdjustedFrame(frame),
		mTextureFrame(0, 0, 1, 1),
		mVisibility(ViewVisible),
		mZPosition(-1),
		mBackgroundImage(NULL),
		mBackgroundImageAtlas(NULL),
		mParent(NULL),
		mSprite(NULL),
		mBackgroundImageChanged(false),
		mClipSubviews(false),
		mFocused(false),
		mWindow(NULL),
		mBorderWidth(0),
		mAlpha(1),
		mHoriAlign(HorizontalAlignLeft),
		mVertAlign(VerticalAlignTop),
		mRotation(0),
		mLayoutInvalid(true)
	{
		mFrameSet = (frame.origin.x != 0 || frame.origin.y != 0 ||
			frame.size.width != 0 || frame.size.height != 0);
	}

	View::~View()
	{
		TViewList subviews = this->RemoveAllSubviews();
		for (View *subview : subviews) {
			delete subview;
		}

		this->SetFocused(false);
		if (this->GetParent()) {
			this->RemoveFromSuperview();
		}
	}

	void View::SafeDelete()
	{
		Dispatch::PushTask(Dispatch::MainQueue, [this]() {
			delete this;
		});
	}

	void View::AddSubview(View * view)
	{
		bool found = false;
		for(int i = 0; i < mSubviews.size(); i++) {
			if(mSubviews[i] == view) {
				found = true;
			}
		}

		if(!found) {
			mSubviews.push_back(view);
			view->SetParent(this);
			if (view->GetZPosition() < 0) {
				view->SetZPosition(mZPosition + 1);
			}
		}

		this->InvalidateLayout();
	}

	View * View::RemoveSubview(View *view)
	{
		for (auto it = mSubviews.begin(); it != mSubviews.end(); ++it) {
			if (*it == view) {
				view->SetParent(NULL);
				mSubviews.erase(it);
				return view;
			}
		}

		this->InvalidateLayout();

		return NULL;
	}

	TViewList View::RemoveAllSubviews()
	{
		auto subviews = mSubviews;
		for (View *subview : subviews) {
			this->RemoveSubview(subview);
		}

		mSubviews.clear();

		this->InvalidateLayout();

		return subviews;
	}

	void View::RemoveFromSuperview()
	{
		this->SetFocused(false);

		auto parent = this->GetParent();
		if (parent) {
			parent->RemoveSubview(this);
		}

		this->InvalidateLayout();
	}

	void View::Update(int deltaMillis)
	{
		for(int j = 0; j < mSubviews.size(); j++) {
			mSubviews[j]->Update(deltaMillis);
		}

		std::sort(mSubviews.begin(), mSubviews.end(), 
		[](View * v1, View * v2) -> bool {
			return v1->GetZPosition() < v2->GetZPosition();
		});
	}

	void View::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		mAdjustedFrame = Frame(
			mFrame.origin.x + parentFrame.origin.x,
			mFrame.origin.y + parentFrame.origin.y,
			mFrame.size.width,
			mFrame.size.height
		);

		if(mVisibility == ViewVisible) {
			if(!mSprite) {
				mSprite = new SpriteShape(device, "sprite");
			}
			

			mSprite->SetBackgroundColor(glm::vec4(mBackgroundColor.red, mBackgroundColor.green, 
				mBackgroundColor.blue, mBackgroundColor.alpha * mAlpha));

			if (mBackgroundImage || mBackgroundImageAtlas) {
				if(mBackgroundImageChanged) {
					if (mBackgroundImageAtlas) {
						mSprite->SetBackgroundImage(mBackgroundImageAtlas.get(), mBackgroundImageKey);
					}
					else if (mBackgroundImage) {
						mSprite->SetBackgroundImage(mBackgroundImage.get());
					}

					//mSprite->SetTextureFrame(0.0, 9, 1.0, 0.5);
					mBackgroundImageChanged = false;
				}
			} else {
				mSprite->SetBackgroundImage(NULL);
			}

			if (mBorderWidth) {
				mSprite->SetBorderColor(mBorderColor);
				mSprite->SetBorderWidth(mBorderWidth);
			}

			/*mTextureFrame = Frame(0, 0, 1, 1);
			if(parentFrame.origin.y < 0) {
				real ratio = abs(mAdjustedFrame.origin.y) / mFrame.size.height;
				mTextureFrame.origin.y = ratio;
				mTextureFrame.size.height = 1.0f - ratio;
				mAdjustedFrame.size.height *= ratio;
			}

			mSprite->SetTextureFrame(mTextureFrame);*/

			if (this->GetWindow() &&
				this->GetWindow()->GetFrame().Contains(mAdjustedFrame.origin)) {
				mSprite->SetFrame(mAdjustedFrame);
				mSprite->Draw(device, state);

				Frame inheritedFrame = this->CalculateChildFrame();

				if (mClipSubviews) {
					device->PushScissorRect(mAdjustedFrame.origin.x,
						mAdjustedFrame.origin.y,
						mAdjustedFrame.size.width,
						mAdjustedFrame.size.height);
				}

				for (int i = 0; i < mSubviews.size(); i++) {
					View * child = mSubviews[i];
					child->Render(device, state, inheritedFrame);
				}

				if (mClipSubviews) {
					device->PopScissorRect();
				}
			}
		}
	}

	void View::SetBackgroundImage(std::wstring imageName)
	{
		mBackgroundImageAtlas = NULL;
		mBackgroundImage = std::shared_ptr<Image>(new Image(imageName));
		mBackgroundImageChanged = true;

		this->InvalidateLayout();
	}

	void View::SetBackgroundImage(std::shared_ptr<Image> image)
	{
		mBackgroundImageAtlas = NULL;
		mBackgroundImage = image;
		if(mFrame.size.width == 0 || mFrame.size.height == 0) {
			mFrame.size = image->GetSize();
		}
		mBackgroundImageChanged = true;

		this->InvalidateLayout();
	}

	void View::SetBackgroundImage(std::shared_ptr<ImageAtlas> atlas, const std::string &key)
	{
		mBackgroundImage = NULL;
		mBackgroundImageAtlas = atlas;
		mBackgroundImageKey = key;
		if (mFrame.size.width == 0 || mFrame.size.height == 0) {
			mFrame.size = atlas->GetImageSize(key);
		}
		mBackgroundImageChanged = true;

		this->InvalidateLayout();
	}

	void View::SetFocused(bool focused)
	{
		auto window = this->GetWindow();

		if (window) {
			if (focused) {
				this->GetWindow()->SetFocusedView(this);
			}

			else {
				this->GetWindow()->SetFocusedView(NULL);
			}

			mFocused = focused;
		}
	}

	void View::SetVisibility(ViewVisibility visibility)
	{
		mVisibility = visibility;

		this->InvalidateLayout();
	}

	void View::ClipSubviews(bool clip)
	{
		mClipSubviews = clip;

		this->InvalidateLayout();
	}

	Window* View::GetWindow()
	{
		if(mWindow) {
			return mWindow;
		} else if(mParent) {
			return mParent->GetWindow();
		}

		return NULL;
	}

	bool View::IsFocused()
	{
		for (View *subview : mSubviews) {
			if (subview->IsFocused()) {
				return true;
			}
		}

		return mFocused;
	}

	/* Event Delegates */
	void View::AddMouseEvent(MouseEventType type, MouseEventDelegate eventDelegate)
	{
		mMouseDelegates[type].push_back(eventDelegate);
	}

	void View::AddKeyboardEvent(KeyboardEventType type, KeyboardEventDelegate eventDelegate)
	{
		mKeyboardDelegates[type].push_back(eventDelegate);
	}

	bool View::ProcessMouseEvent(const MouseEvent &e)
	{
		return ContainsPoint(e.position);
	}


	View* View::GetSelectedView(const Point &p)
	{
		View * selectedView = NULL;

		if(mVisibility == ViewVisible) {
			if(mClipSubviews && !this->ContainsPoint(p)) {
				return NULL;
			}

			for(int i = mSubviews.size() - 1; i >= 0; i--) {
				View * next = mSubviews[i];
				selectedView = next->GetSelectedView(p);
				if(selectedView) {
					break;
				}
			}

			if(this->ContainsPoint(p)) {
				if(!selectedView) {
					selectedView = this;
				}
			}
		}

		return selectedView;
	}

	bool View::ProcessKeyboardEvent(const KeyboardEvent &e)
	{
		return false; // Keyboard events are undefined for default controls
	}

	bool View::OnKeyboardEvent(const KeyboardEvent &e)
	{
		if (mKeyboardDelegates.size() > 0 &&
			mKeyboardDelegates[e.type].size() > 0) {
			std::vector<KeyboardEventDelegate> delegates = mKeyboardDelegates[e.type];

			for (int i = 0; i < delegates.size(); i++) {
				delegates[i](this, e);
			}
		}

		return false;
	}

	bool View::OnMouseEvent(const MouseEvent &e)
	{
		if (mMouseDelegates.size() > 0 &&
			mMouseDelegates[e.type].size() > 0) {
			std::vector<MouseEventDelegate> delegates = mMouseDelegates[e.type];

			for (int i = 0; i < delegates.size(); i++) {
				delegates[i](this, e);
			}

			return true;
		}

		return false;
	}

	void View::AddInternalSubview(View * view)
	{
		this->AddSubview(view);
		view->SetZPosition(view->mZPosition + 10000);
		mInternalSubviews.push_back(view);

		this->InvalidateLayout();
	}

	View * View::FindViewById(const std::string &id)
	{
		for(View * subview : mSubviews) {
			if(subview->mId == id) {
				return subview;
			}

			View * subviewSearch = subview->FindViewById(id);
			if(subviewSearch) {
				return subviewSearch;
			}
		}

		return NULL;
	}

	View * View::FindView(View *view)
	{
		if (view == this) {
			return this;
		}

		for (View *subview : mSubviews) {
			if (subview == view) {
				return subview;
			}

			View *subsubview = subview->FindView(subview);
			if (subsubview) {
				return subsubview;
			}
		}

		return NULL;
	}

	void View::SetAttribute(const std::string &name, const std::string &value)
	{
		mAttributes[name] = value;
	}

	std::string View::GetAttribute(const std::string &name)
	{
		auto it = mAttributes.find(name);
		if (it != mAttributes.end()) {
			return mAttributes[name];
		}

		return std::string();
	}

	void View::ParseFromXML(XMLNode &node)
	{
		mFrameSet = node.GetAttributeString("frame") != "";

		if (node.HasAttribute("frame")) {
			this->SetFrame(ViewXMLParser::ParseFrame(node.GetAttributeString("frame")));
		}
		else {
			if (node.HasAttribute("size")) {
				this->SetSize(ViewXMLParser::ParseSize(node.GetAttributeString("size")));
			}
			else {
				std::string width = "0", height = "0";

				if (node.HasAttribute("width")) {
					width = node.GetAttributeString("width");
				}

				if (node.HasAttribute("height")) {
					height = node.GetAttributeString("height");
				}

				this->SetSize(ViewXMLParser::ParseSize(width + "," + height));
			}

			if (node.HasAttribute("position")) {
				this->SetPosition(ViewXMLParser::ParsePoint(node.GetAttributeString("position")));
			}
			else {
				if (node.HasAttribute("x")) {
					this->SetX(node.GetAttributeFloat("x"));
				}

				if (node.HasAttribute("y")) {
					this->SetY(node.GetAttributeFloat("y"));
				}
			}
		}

		if (node.HasAttribute("z_index")) {
			this->SetZPosition(node.GetAttributeFloat("z_index"));
		}
		
		if (node.HasAttribute("padding")) {
			this->SetPadding(ViewXMLParser::ParseRect(node.GetAttributeString("padding")));
		}
		else {
			Rect padding;
			if (node.HasAttribute("padding_left")) {
				padding.left = node.GetAttributeFloat("padding_left");
			} 

			if (node.HasAttribute("padding_right")) {
				padding.right = node.GetAttributeFloat("padding_right");
			}

			if (node.HasAttribute("padding_top")) {
				padding.top = node.GetAttributeFloat("padding_top");
			}

			if (node.HasAttribute("padding_bottom")) {
				padding.bottom = node.GetAttributeFloat("padding_bottom");
			}

			this->SetPadding(padding);
		}
		
		if (node.HasAttribute("margin")) {
			this->SetMargin(ViewXMLParser::ParseRect(node.GetAttributeString("margin")));
		}
		else {
			Rect margin;
			if (node.HasAttribute("margin_left")) {
				margin.left = node.GetAttributeFloat("margin_left");
			}

			if (node.HasAttribute("margin_right")) {
				margin.right = node.GetAttributeFloat("margin_right");
			}

			if (node.HasAttribute("margin_top")) {
				margin.top = node.GetAttributeFloat("margin_top");
			}

			if (node.HasAttribute("margin_bottom")) {
				margin.bottom = node.GetAttributeFloat("margin_bottom");
			}

			this->SetMargin(margin);
		}

		const std::string &bgImage = node.GetAttributeString("background_image");
		if (bgImage.length() > 0) {
			this->SetBackgroundImage(bgImage);
		}
		else {
			const std::string &bgColorText = node.GetAttributeString("background_color");
			if (bgColorText.length() != 0) {
				this->SetBackgroundColor(Color::FromHexString(bgColorText));
			}
		}
		
		this->SetId(node.GetAttributeString("id"));

		const std::string &visibility = node.GetAttributeString("visibility");
		if (visibility == "invisible") {
			this->SetVisibility(ViewInvisible);
		}
		else if (visibility == "gone") {
			this->SetVisibility(ViewGone);
		}
		else {
			this->SetVisibility(ViewVisible);
		}
		

		const TXMLAttributeMap &attrs = node.GetAttributes();
		for (auto &pair : attrs) {
			this->SetAttribute(pair.second.GetName(), pair.second.GetValue());
		}

		const std::string &horiAlign = node.GetAttributeString("halign");
		if (horiAlign == "left") {
			mHoriAlign = HorizontalAlignLeft;
		}
		else if (horiAlign == "center") {
			mHoriAlign = HorizontalAlignCenter;
		}
		else if (horiAlign == "right") {
			mHoriAlign = HorizontalAlignRight;
		}

		const std::string &vertAlign = node.GetAttributeString("valign");
		if (vertAlign == "top") {
			mVertAlign = VerticalAlignTop;
		}
		else if (vertAlign == "middle") {
			mVertAlign = VerticalAlignMiddle;
		}
		else if (vertAlign == "bottom") {
			mVertAlign = VerticalAlignBottom;
		}

		/* Layout params */
		mLayoutParams.alignParentBottom = node.GetAttributeBoolean("align_parent_bottom");
		mLayoutParams.alignParentLeft = node.GetAttributeBoolean("align_parent_left");
		mLayoutParams.alignParentRight = node.GetAttributeBoolean("align_parent_right");
		mLayoutParams.alignParentTop = node.GetAttributeBoolean("align_parent_top");

		mLayoutParams.aboveViewId = node.GetAttributeString("above");
		mLayoutParams.belowViewId = node.GetAttributeString("below");
		mLayoutParams.leftOfViewId = node.GetAttributeString("left_of");
		mLayoutParams.rightOfViewId = node.GetAttributeString("right_of");

		mLayoutParams.layoutWeight = node.GetAttributeInt("weight");
		mLayoutParams.alignment = AlignmentInherit;
		mLayoutParams.subviewAlignment = AlignmentInherit;
	}

	void View::OnXMLParseComplete()
	{
	}

	void View::InvalidateLayout()
	{
		mLayoutInvalid = true;
	}

	void View::Measure(const Size &parentSize)
	{
		if (mVisibility == ViewGone) {
			this->SetSize(0, 0);
		}
		else {
			Size newSize = mFrame.size;

			if (mLayoutParams.size.width == MATCH_PARENT) {
				newSize.width = parentSize.width;
			}

			if (mLayoutParams.size.height == MATCH_PARENT) {
				newSize.height = parentSize.height;
			}

			Size measureSize = newSize;
			if (mLayoutParams.size.width == WRAP_CONTENT) {
				measureSize.width = parentSize.width;
			}

			if (mLayoutParams.size.height == WRAP_CONTENT) {
				measureSize.height = parentSize.height;
			}

			for (View *view : mSubviews) {
				if (view->GetVisibility() != ViewVisible) {
					continue;
				}

				Size viewMeasureSize = measureSize;
				const Rect &viewMargin = view->GetMargin();
				const Rect &viewPadding = view->GetPadding();

				viewMeasureSize.width = viewMeasureSize.width - viewMargin.right - viewMargin.left - mPadding.left - 
					mPadding.right - mMargin.right - mMargin.left - viewPadding.right - viewPadding.left;
				viewMeasureSize.height = viewMeasureSize.height - viewMargin.bottom - viewMargin.top - mPadding.top - 
					mPadding.bottom - mMargin.bottom - viewPadding.bottom - viewPadding.top;

				view->Measure(viewMeasureSize);
			}

			this->SetSize(newSize);
		}

		mLayoutInvalid = false;
	}

	View * View::CreateFromResource(const std::wstring &resource)
	{
		Asset asset(resource);
		View *view = ViewXMLParser::Parse(&asset);
		if (view) {
			view->OnLoadComplete();
		}

		return view;
	}

	void View::RegisterViewClass(const std::string &name, TViewCreatorFunction creator)
	{
		sViewCreatorRegistry[name] = creator;
	}

	Point View::GetPositionInView(const Point &position, View *other)
	{
		if (!other || other == this) {
			return position;
		}

		Point newPos(position.x + mFrame.origin.x, position.y + mFrame.origin.y);
		
		return mParent->GetPositionInView(newPos, other);
	}
};
