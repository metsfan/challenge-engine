#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <d3dx9math.h>
#include "ViewManager.h"

namespace challenge
{
	ViewManager::ViewManager(const Size &screenSize) :
		mRootView(NULL),
		mFocusedView(NULL)
	{
		mCamera = new OrthoCamera(0.0f, screenSize.width, screenSize.height, 0.0f, -1000.0f, 1000.0f, screenSize);

		this->RegisterCoreUIClasses();
	}
	ViewManager::~ViewManager()
	{
	}

	void ViewManager::SetRootView(View *view)
	{
		mRootView = view;
	}

	void ViewManager::SetFocusedView(View *view)
	{
		if (mFocusedView) {
			mFocusedView->mFocused = false;
		}

		mFocusedView = view;
	}

	void ViewManager::UnfocusView(View *view)
	{
		if (mFocusedView == view) {
			mFocusedView = NULL;
			view->mFocused = false;
		}
	}

	void ViewManager::Update(int deltaMillis)
	{
		if(mRootView) {
			mRootView->Update(deltaMillis);
		}
	}

	void ViewManager::Render(IGraphicsDevice *device)
	{
		if(mRootView) {
			RenderState state;

			state.SetProjection(mCamera->GetProjectionMatrix());

			//state.PushTransform(mCamera->GetViewMatrix());
			device->DisableState(DepthTest);
			device->EnableState(AlphaBlending);
			mRootView->Render(device, state, Frame());
		}
	}

	bool ViewManager::ProcessKeyboardEvent(const KeyboardEvent &e)
	{
		if(!mRootView) {
			return false;
		}

		View *selectedView = mFocusedView;
		bool handled = false;

		while(selectedView) {
			if(selectedView->mKeyboardDelegates.size() > 0 &&
				selectedView->mKeyboardDelegates[e.type].size() > 0) {
				std::vector<KeyboardEventDelegate> delegates = selectedView->mKeyboardDelegates[e.type];

				for(int i = 0; i < delegates.size(); i++) {
					delegates[i](selectedView, e);
				}

				handled = true;
			}

			selectedView = selectedView->GetParent();
		}

		return handled;
	}

	bool ViewManager::ProcessMouseEvent(const MouseEvent &e)
	{
		if(!mRootView) {
			return false;
		}

		bool handled = false;

		if(e.type == MouseEventMouseWheelMove) {
			View *selectedView = mFocusedView;
			while(selectedView) {
				if(selectedView->mMouseDelegates.size() > 0 &&
					selectedView->mMouseDelegates[e.type].size() > 0) {
					std::vector<MouseEventDelegate> delegates = selectedView->mMouseDelegates[e.type];

					for(int i = 0; i < delegates.size(); i++) {
						delegates[i](selectedView, e);
					}

					handled = true;
				} 

				selectedView = selectedView->GetParent();
			}
		} else {
			View *selectedView = mRootView->GetSelectedView(e.position);
			if(e.type == MouseEventMouseDown) {
				if(mFocusedView) {
					mFocusedView->SetFocused(false);
				}

				mFocusedView = selectedView;
				mFocusedView->SetFocused(true);
			}

			
			while (selectedView) {
				if(selectedView->mMouseDelegates.size() > 0 &&
					selectedView->mMouseDelegates[e.type].size() > 0) {
					std::vector<MouseEventDelegate> delegates = selectedView->mMouseDelegates[e.type];

					for(int i = 0; i < delegates.size(); i++) {
						delegates[i](selectedView, e);
					}

					handled = true;
				} 

				selectedView = selectedView->GetParent();
			}
		}
		
		return handled;
	}

	void ViewManager::RegisterCoreUIClasses()
	{
		View::RegisterViewClass("View", [](Frame frame) { return new View(frame); });
		View::RegisterViewClass("Button", [](Frame frame) { return new ButtonView(frame); });
		View::RegisterViewClass("Checkbox", [](Frame frame) { return new CheckboxView(frame); });
		View::RegisterViewClass("Form", [](Frame frame) { return new Form(frame); });
		View::RegisterViewClass("Label", [](Frame frame) { return new LabelView(frame); });
		View::RegisterViewClass("Options", [](Frame frame) { return new OptionsView(frame); });
		View::RegisterViewClass("Panel", [](Frame frame) { return new PanelView(frame); });
		View::RegisterViewClass("SelectList", [](Frame frame) { return new SelectListView(frame); });
		View::RegisterViewClass("TextField", [](Frame frame) { return new TextFieldView(frame); });
	}
};