#include <chrono>

#include <Challenge/Challenge.h>
#include "GameApplicationWindows.h"
#include <Challenge/Platform/Win32/CWindow.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>
#include <Challenge/UI/ViewManager.h>
#include <Challenge/Model/ModelManager.h>
#include <Challenge/Input/InputManager.h>
#include <Challenge/Event/EventManager.h>
#include <Challenge/Database/DatabaseManager.h>

namespace challenge
{
	GameApplicationWindows::GameApplicationWindows(std::shared_ptr<Window> window, 
													std::shared_ptr<IApplicationListener> listener, 
													HINSTANCE instance, 
													HWND winHandle) :
		GameApplication(window, listener),
		mInstance(instance),
		mWinHandle(winHandle)
	{
	}

	GameApplicationWindows::~GameApplicationWindows(void)
	{
	}

	bool GameApplicationWindows::Initialize()
	{
		GRAPHICS_DEVICE_DESC graphicsDesc;
		graphicsDesc.MultiSampling = MultisampleLevelNone;
		mGraphicsDevice = CreateGraphicsDevice<RendererTypeDX11>(graphicsDesc, mWinHandle, this->GetWindow()->GetSize());

		this->LoadShaderConfig(L"shaders.xml");
		this->LoadEffectsConfig(L"effects.xml");

		/*mDatabaseManager = new DatabaseManager();
		if(!mDatabaseManager->Initialize()) {
			return false;
		}

		mEventManager = new EventManager();

		mModelManager = new ModelManager();
		if(!mModelManager->Initialize()) {
			return false;
		}

		mInputManager = new InputManager();
		mInputManager->AddKeyboardListener(mViewManager);
		mInputManager->AddMouseListener(mViewManager);

		mPhysicsManager = new PhysicsManager();
		mEventManager->RegisterEvent("actor_added", mPhysicsManager);
		mEventManager->RegisterEvent("actor_moved", mPhysicsManager);*/

		mInitialized = true;

		mGameInstance = this;

		return GameApplication::Initialize();
	}
};

