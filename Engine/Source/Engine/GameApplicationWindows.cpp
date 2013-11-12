#include <chrono>

#include <Engine/Challenge.h>
#include "GameApplicationWindows.h"
#include <Engine/UI/Window/WindowWindows.h>
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>
#include <Engine/UI/ViewManager.h>
#include <Engine/Model/ModelManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Physics/PhysicsManager.h>
#include <Engine/Event/EventManager.h>
#include <Engine/Database/DatabaseManager.h>

namespace challenge
{
	GameApplicationWindows::GameApplicationWindows(const Size &screenSize, HINSTANCE instance, HWND window) :
		GameApplication(screenSize),
		mInstance(instance),
		mWinHandle(window)
	{
	}

	GameApplicationWindows::~GameApplicationWindows(void)
	{
	}

	bool GameApplicationWindows::Initialize()
	{
		if (!mInstance) {
			return false;
		}

		if (!GameApplication::Initialize()) {
			return false;
		}

		// Initialize window
		/*mWindow = new challenge::GameWindowWindows("Dungeon Raider v0.1", mInstance);
		if (!mWindow->Initialize(1280, 1024)) {
			return false;
		}
	
		RendererDX11 *renderer = new RendererDX11();
		// Setting the renderer will also internally initialize it
		if (!mWindow->SetRenderer(renderer)) {
			return false;
		}*/

		/*const Size &screenSize = this->GetScreenSize();

		auto window = new Window<PlatformTypeWin32>(mInstance, "Dungeon Raider v0.1", screenSize);
		if(!window->Initialize()) {
			return false;
		}
		window->SetWindowVisibility(WindowVisible);
		window->SetInputReader(mInputManager);

		mWinHandle = window->GetWinHandle();
		mWindow = window;*/

		GRAPHICS_DEVICE_DESC graphicsDesc;
		graphicsDesc.MultiSampling = MultisampleLevelNone;
		mGraphicsDevice = CreateGraphicsDevice<RendererTypeDX11>(graphicsDesc, mWinHandle, mScreenSize);

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

		return true;
	}

	void GameApplicationWindows::RunMainLoop(AppCallback updateCallback, AppCallback renderCallback)
	{
		MSG msg;

		int desiredFPS = 60;
		int frameTime = 1000000 / desiredFPS;

		int deltaMillis = 0;
		LARGE_INTEGER time1, time2, freq;
		QueryPerformanceCounter(&time2);
		QueryPerformanceFrequency(&freq);

		this->StartRunning();

		int totalTime = 0;
		int frames = 0;

		while (this->IsRunning())
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				GetMessage(&msg, NULL, 0, 0);
				DispatchMessage(&msg);
			}
			
			QueryPerformanceCounter(&time1);
			deltaMillis = (time1.QuadPart - time2.QuadPart) * 0.000001;

			this->Update();
			updateCallback(deltaMillis);

			this->PreRender();
			//this->Render();
			renderCallback(deltaMillis);
			mViewManager->Render(mGraphicsDevice);
			this->PostRender();
			QueryPerformanceCounter(&time2);
			LONG64 time = ((time2.QuadPart - time1.QuadPart) * 1000000) / freq.QuadPart;

			int dif = frameTime - time;
			if (dif > 0) {
				std::this_thread::sleep_for(std::chrono::microseconds(dif));
			}

			time2 = time1;
		}
	}
};

