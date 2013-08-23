#include <Engine/Challenge.h>
#include <Engine/UI/UIManager.h>
#include <Engine/Util/Image.h>
//#include <Engine/Util/TextureAtlas.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/Window.h>
#include "View.h"

namespace challenge
{
	View::View(Frame frame) :
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
		mUIManager(NULL)
	{
	}

	View::~View()
	{
	}

	void View::AddSubview(View *view)
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

		View *rootView = this;
		while(rootView->GetParent()) {
			rootView = rootView->GetParent();
		}
		view->mRootView = rootView;
		view->mUIManager = rootView->mUIManager;
	}

	void View::Update(int deltaMillis)
	{
		for(int j = 0; j < mSubviews.size(); j++) {
			mSubviews[j]->Update(deltaMillis);
		}

		std::sort(mSubviews.begin(), mSubviews.end(), 
		[](View *v1, View *v2) -> bool {
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

			mSprite->SetBackgroundColor(mBackgroundColor);

			if(mBackgroundImage) {
				if(mBackgroundImageChanged) {
					mSprite->SetBackgroundImage(mBackgroundImage.get());
					//mSprite->SetTextureFrame(0.0, 9, 1.0, 0.5);
					mBackgroundImageChanged = false;
				}
			} else {
				mSprite->SetBackgroundImage(NULL);
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
			for(int i = 0; i < mSubviews.size(); i++) {
				if(mClipSubviews) {
					device->EnableState(ScissorTest);
					device->SetScissorRect(mAdjustedFrame.origin.x, 
						mAdjustedFrame.origin.y, 
						mAdjustedFrame.size.width, 
						mAdjustedFrame.size.height);
				}

				View *child = mSubviews[i];
				child->Render(device, state, inheritedFrame);

				if(mClipSubviews) {
					device->DisableState(ScissorTest);
				}
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
		mFocused = focused;
		if(mUIManager) {
			mUIManager->mFocusedView = this;
		}
	}

	/* Event Delegates */

	void View::AddMouseDownDelegate(MouseEventDelegate eventDelegate)
	{
		mMouseDelegates[MouseEventMouseDown].push_back(eventDelegate);
	}

	void View::AddMouseUpDelegate(MouseEventDelegate eventDelegate)
	{
		mMouseDelegates[MouseEventMouseUp].push_back(eventDelegate);
	}

	void View::AddMouseClickDelegate(MouseEventDelegate eventDelegate)
	{
		mMouseDelegates[MouseEventMouseClick].push_back(eventDelegate);
	}

	void View::AddMouseMoveDelegate(MouseEventDelegate eventDelegate)
	{
		mMouseDelegates[MouseEventMouseMove].push_back(eventDelegate);
	}

	void View::AddMouseWheelMoveDelegate(MouseEventDelegate eventDelegate)
	{
		mMouseDelegates[MouseEventMouseWheelMove].push_back(eventDelegate);
	}

	void View::AddKeyDownDelegate(KeyboardEventDelegate eventDelegate)
	{
		mKeyboardDelegates[KeyboardEventKeyDown].push_back(eventDelegate);
	}

	void View::AddKeyUpDelegate(KeyboardEventDelegate eventDelegate)
	{
		mKeyboardDelegates[KeyboardEventKeyUp].push_back(eventDelegate);
	}

	bool View::ProcessMouseEvent(const MouseEvent &e)
	{
		return ContainsPoint(e.position);
	}

	View* View::GetSelectedView(const Point &p)
	{
		View *selectedView = NULL;

		if(mVisible) {
			if(mClipSubviews && !this->ContainsPoint(p)) {
				return NULL;
			}

			for(int i = mSubviews.size() - 1; i >= 0; i--) {
				View *next = mSubviews[i];
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

	void View::AddInternalSubview(View *view)
	{
		this->AddSubview(view);
		view->SetZPosition(view->mZPosition + 10000);
		mInternalSubviews.push_back(view);
	}
};
