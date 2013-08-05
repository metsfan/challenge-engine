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
	View::View() :
		mFrame(Frame(0, 0, 0, 0)),
		mAdjustedFrame(mFrame),
		mVisible(true),
		mZPosition(0),
		mBackgroundImage(NULL),
		mParent(NULL)
	{
	}

	View::View(Frame frame) :
		mFrame(frame),
		mAdjustedFrame(frame),
		mVisible(true),
		mZPosition(0),
		mBackgroundImage(NULL),
		mParent(NULL)
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
	}

	void View::Update(int deltaMillis)
	{
		for(int j = 0; j < mSubviews.size(); j++) {
			mSubviews[j]->Update(deltaMillis);
		}
	}

	void View::Render(IGraphicsDevice *device, RenderState &state)
	{
		if(mVisible) {
			if(!mSprite) {
				mSprite = new SpriteShape(device);
			}

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(mFrame.origin.x, mFrame.origin.y, 0.0f));
			transform = glm::scale(transform, glm::vec3(mFrame.size.width, mFrame.size.height, 1.0f));

			state.PushTransform(transform);

			mSprite->SetBackgroundColor(mBackgroundColor);

			if(mBackgroundImage) {
				mSprite->SetBackgroundImage(mBackgroundImage);
			} else {
				mSprite->SetBackgroundImage(NULL);
			}

			mSprite->Draw(device, state);

			for(int i = 0; i < mSubviews.size(); i++) {
				View *child = mSubviews[i];
				child->Render(device, state);
			}
		}
	}

	void View::SetBackgroundImage(std::string imageName)
	{
		mBackgroundImage = new Image(imageName);
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

	void View::AddKeyDownDelegate(KeyboardEventDelegate eventDelegate)
	{
		mKeyboardDelegates[KeyboardEventKeyDown].push_back(eventDelegate);
	}

	void View::AddKeyUpDelegate(KeyboardEventDelegate eventDelegate)
	{
		mKeyboardDelegates[KeyboardEventKeyUp].push_back(eventDelegate);
	}

	bool View::OnMouseEvent(const MouseEvent &e)
	{
		bool handled = false;
		if(mSubviews.size() > 0) {
			View *topControl = NULL;
			for(int i = mSubviews.size() - 1; i >= 0; i--) {
				View *next = mSubviews[i];
				if(next->ProcessMouseEvent(e)) {
					if(topControl == NULL ||
						topControl->mZPosition < next->mZPosition) {
						topControl = next;
					}
				}
			}

			if(topControl != NULL) {
				topControl->OnMouseEvent(e);
				handled = true;
			}
		}
	
		if(!handled) {
			if(mMouseDelegates.size() > 0 && ProcessMouseEvent(e)) {
				std::vector<MouseEventDelegate> delegates = mMouseDelegates[e.type];

				for(int i = 0; i < delegates.size(); i++) {
					delegates[i](this, e);
				}

				return true;
			}
		}

		return false;
	}

	bool View::ProcessMouseEvent(const MouseEvent &e)
	{
		return ContainsPoint(e.position);
	}

	bool View::OnKeyboardEvent(const KeyboardEvent &e)
	{
		if(mKeyboardDelegates.size() > 0 && ProcessKeyboardEvent(e)) {
			std::vector<KeyboardEventDelegate> delegates = mKeyboardDelegates[e.type];

			for(int i = 0; i < delegates.size(); i++) {
				delegates[i](this, e);
			}

			return true;
		}

		for(int i = 0; i < mSubviews.size(); i++) {
			if(mSubviews[i]->OnKeyboardEvent(e)) {
				return true;
			}
		}

		return false;
	}

	bool View::ProcessKeyboardEvent(const KeyboardEvent &e)
	{
		return false; // Keyboard events are undefined for default controls
	}
};
