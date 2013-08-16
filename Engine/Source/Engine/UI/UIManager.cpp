#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <d3dx9math.h>
#include "UIManager.h"

namespace challenge
{
	UIManager::UIManager(const Size &screenSize) :
		mRootView(NULL)
	{
		mCamera = new OrthoCamera(0.0f, screenSize.width, screenSize.height, 0.0f, -1000.0f, 1000.0f, screenSize);
	}
	UIManager::~UIManager()
	{
	}

	void UIManager::SetRootView(View *view)
	{
		mRootView = view;
	}

	void UIManager::Update(int deltaMillis)
	{
		if(mRootView) {
			mRootView->Update(deltaMillis);
		}
	}

	void UIManager::Render(IGraphicsDevice *device)
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

	void UIManager::AddImageToAtlas(Image *image)
	{
		//mImageAtlas->AddBitmap(image->GetBits(), image->GetWidth(), image->GetHeight(), image->GetFilename());
	}

	/*TextureAtlasEntry UIManager::GetImageForKey(std::string key)
	{
		return mImageAtlas->GetEntryForKey(key);
	}*/

	UIManager* UIManager::GetDefaultManager() {
		GameApplication *gApp = GameApplication::GetInstance();
		return gApp->GetUIManager();
	}

	bool UIManager::ProcessKeyboardEvent(const KeyboardEvent &e)
	{
		if(mFocusedView &&
			mFocusedView->mKeyboardDelegates.size() > 0 &&
			mFocusedView->mKeyboardDelegates[e.type].size() > 0) {
			std::vector<KeyboardEventDelegate> delegates = mFocusedView->mKeyboardDelegates[e.type];

			for(int i = 0; i < delegates.size(); i++) {
				delegates[i](mFocusedView, e);
			}

			return true;
		}

		return false;
	}

	bool UIManager::ProcessMouseEvent(const MouseEvent &e)
	{
		View *selectedView = mRootView->GetSelectedView(e.position);

		while (selectedView) {
			if(selectedView->mMouseDelegates.size() > 0 &&
				selectedView->mMouseDelegates[e.type].size() > 0) {
				std::vector<MouseEventDelegate> delegates = selectedView->mMouseDelegates[e.type];

				for(int i = 0; i < delegates.size(); i++) {
					delegates[i](selectedView, e);
				}

				if(e.type == MouseEventMouseDown) {
					mFocusedView = selectedView;
				}

				return true;
			} 

			selectedView = selectedView->GetParent();
		}

		mFocusedView = NULL;

		return false;
	}
};