#include <Engine/Challenge.h>
#include <Engine/UI/View.h>
#include <Engine/UI/ViewManager.h>
#include <Engine/Util/Image.h>
//#include <Engine/Util/TextureAtlas.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/GameApplication.h>
#include <Engine/UI/Window.h>
#include <Engine/UI/ViewXMLParser.h>
#include <Engine/Input/InputManager.h>

#include <Engine/UI/Layout/AbsoluteLayout.h>
#include <Engine/UI/Layout/LinearLayout.h>

namespace challenge
{
	std::map<std::string, TViewCreatorFunction> View::sViewCreatorRegistry;

	View::View(Frame frame, LayoutType layout) :
		mFrame(frame),
		mAdjustedFrame(frame),
		mTextureFrame(0, 0, 1, 1),
		mVisible(true),
		mZPosition(0),
		mBackgroundImage(NULL),
		mParent(NULL),
		mSprite(NULL),
		mBackgroundImageChanged(false),
		mClipSubviews(false),
		mFocused(false),
		mWindow(NULL),
		mBorderWidth(0)
	{
		this->SetLayoutType(layout);

		mFrameSet = (frame.origin.x != 0 || frame.origin.y != 0 ||
			frame.size.width != 0 || frame.size.height != 0);
	}

	View::~View()
	{
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
			view->SetZPosition(mZPosition + 1);
		}

		this->PositionSubviews();
	}

	void View::RemoveSubview(View *view)
	{
		for (auto it = mSubviews.begin(); it != mSubviews.end(); ++it) {
			if (*it == view) {
				mSubviews.erase(it);
				return;
			}
		}
	}

	void View::RemoveFromSuperview()
	{
		auto parent = this->GetParent();
		if (parent) {
			parent->RemoveSubview(this);
		}
	}

	void View::Update(int deltaMillis)
	{
		if (mFrame.size.width < 0) {
			mFrame.size.width = 0;
		}

		if (mFrame.size.height < 0) {
			mFrame.size.height = 0;
		}

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
		if(mVisible) {
			if(!mSprite) {
				mSprite = new SpriteShape(device);
			}
			mAdjustedFrame = Frame(
				mFrame.origin.x + parentFrame.origin.x,
				mFrame.origin.y + parentFrame.origin.y,
				mFrame.size.width,
				mFrame.size.height
			);

			mSprite->SetBackgroundColor(glm::vec4(mBackgroundColor.red, mBackgroundColor.green, mBackgroundColor.blue, mBackgroundColor.alpha));

			if(mBackgroundImage) {
				if(mBackgroundImageChanged) {
					mSprite->SetBackgroundImage(mBackgroundImage.get());
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

			mSprite->SetFrame(mAdjustedFrame);
			mSprite->Draw(device, state);
			
			Frame inheritedFrame = this->CalculateChildFrame();

			if (mClipSubviews) {
				device->PushScissorRect(mAdjustedFrame.origin.x,
					mAdjustedFrame.origin.y,
					mAdjustedFrame.size.width,
					mAdjustedFrame.size.height);
			}

			for(int i = 0; i < mSubviews.size(); i++) {
				View * child = mSubviews[i];
				child->Render(device, state, inheritedFrame);
			}

			if (mClipSubviews) {
				device->PopScissorRect();
			}
		}
	}

	void View::SetBackgroundImage(std::string imageName)
	{
		mBackgroundImage = std::shared_ptr<Image>(new Image(imageName));
		mBackgroundImageChanged = true;
	}

	void View::SetBackgroundImage(std::shared_ptr<Image> image)
	{
		mBackgroundImage = image;
		if(mFrame.size.width == 0 || mFrame.size.height == 0) {
			mFrame.size = image->GetSize();
		}
		mBackgroundImageChanged = true;
	}

	void View::SetFocused(bool focused)
	{
		auto window = this->GetWindow();

		if (window) {
			if (focused) {
				this->GetWindow()->SetFocusedView(this);
			}

			else if (mFocused) {
				this->GetWindow()->UnfocusView(this);
			}

			mFocused = focused;
		}
	}

	void View::ClipSubviews(bool clip)
	{
		mClipSubviews = clip;
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

		if(mVisible) {
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

	void View::AddInternalSubview(View * view)
	{
		this->AddSubview(view);
		view->SetZPosition(view->mZPosition + 10000);
		mInternalSubviews.push_back(view);
	}

	View *  View::FindViewById(const std::string &id)
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

	void View::ParseFromXML(XMLNode &node)
	{
		mFrameSet = node.GetAttributeString("frame") != "";

		this->SetFrame(ViewXMLParser::ParseFrame(node.GetAttributeString("frame")));
		this->SetPadding(ViewXMLParser::ParseRect(node.GetAttributeString("padding")));

		const std::string &layout = node.GetAttributeString("layout");
		if(layout == "linear") {
			const std::string &orientationVal = node.GetAttributeString("orientation");
			LinearLayoutOrientation orientation = LinearLayoutVertical;
			if(orientationVal == "horizontal") {
				orientation = LinearLayoutHorizontal;
			}
			mLayoutEngine = std::unique_ptr<ILayout>(new LinearLayout(orientation));
		} else {
			mLayoutEngine = std::unique_ptr<ILayout>(new AbsoluteLayout());
		}

		const std::string &bgColorText = node.GetAttributeString("background_color");
		if(bgColorText.length() != 0) {
			this->SetBackgroundColor(Color::FromHexString(bgColorText));
		}
		
		this->SetId(node.GetAttributeString("id"));
	}

	void View::SetLayoutType(LayoutType layout)
	{
		switch(layout)
		{
		case LayoutTypeAbsolute:
			mLayoutEngine = std::unique_ptr<ILayout>(new AbsoluteLayout());
			break;

		case LayoutTypeLinear:
			mLayoutEngine = std::unique_ptr<ILayout>(new LinearLayout());
			break;
		};
	}

	void View::PositionSubviews()
	{
		mLayoutEngine->PositionSubviews(this, !mFrameSet);

		if(mParent) {
			mParent->PositionSubviews();
		}
	}

	View * View::CreateFromResource(const std::string &resource)
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
