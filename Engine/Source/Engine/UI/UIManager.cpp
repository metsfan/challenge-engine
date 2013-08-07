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
			mRootView->Render(device, state);
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

	void UIManager::ProcessKeyboardEvent(const KeyboardEvent &e)
	{
		mRootView->OnKeyboardEvent(e);
	}

	void UIManager::ProcessMouseEvent(const MouseEvent &e)
	{
		mRootView->OnMouseEvent(e);
	}

	/* IKeyboardListener methods */
	void UIManager::OnKeyDown(const KeyboardEvent &e)
	{
		ProcessKeyboardEvent(e);
	}

	void UIManager::OnKeyUp(const KeyboardEvent &e)
	{
		ProcessKeyboardEvent(e);
	}

	void UIManager::OnKeyPress(const KeyboardEvent &e)
	{
	}

	/* IMouseListener methods */
	void UIManager::OnMouseDown(const MouseEvent &e)
	{
		ProcessMouseEvent(e);
	}

	void UIManager::OnMouseUp(const MouseEvent &e)
	{
		ProcessMouseEvent(e);
	}

	void UIManager::OnMouseMove(const MouseEvent &e)
	{
		ProcessMouseEvent(e);
	}

	void UIManager::OnMouseClick(const MouseEvent &e)
	{
		ProcessMouseEvent(e);
	}

	void UIManager::OnMouseDblClick(const MouseEvent &e)
	{
		ProcessMouseEvent(e);
	}
};