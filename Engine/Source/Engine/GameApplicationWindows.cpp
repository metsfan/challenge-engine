#include <chrono>

#include <Engine/Challenge.h>
#include "GameApplicationWindows.h"
#include <Engine/Platform/Win32/CWindow.h>
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>
#include <Engine/UI/ViewManager.h>
#include <Engine/Model/ModelManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Physics/PhysicsManager.h>
#include <Engine/Event/EventManager.h>
#include <Engine/Database/DatabaseManager.h>

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

		this->LoadShaderConfig("C:/gamedev/engine-dev/Engine/Engine/Source/Engine/Config/shaders.xml");
		this->LoadEffectsConfig("C:/gamedev/engine-dev/Engine/Engine/Source/Engine/Config/effects.xml");

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

