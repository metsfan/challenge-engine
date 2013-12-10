#include <time.h>
#include <Engine/GameApplicationWindows.h>
#include <Engine/UI/UIManager.h>
#include <Engine/UI/Controls/Button.h>
#include <Engine/Util/Timer.h>
#include <Engine/Util/Logger.h>
using namespace challenge;

void FPSCallback(void *obj);
int nFrames = 0;

void ButtonMouseCallback(UIControl *sender, const MouseEvent &e)
{
	ButtonControl *button = dynamic_cast<ButtonControl *>(sender);
	switch(e.type) 
	{
	case MouseEventMouseDown:
		button->SetBackgroundColor(CColor(122, 0, 0, 1));
		break;

	case MouseEventMouseUp:
		button->SetBackgroundColor(CColor(255, 0, 0, 1));
		break;
	}
};

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	WSADATA wsaData = {0};
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	GameApplicationWindows *winApp = new GameApplicationWindows(hInstance);
	bool initialized = winApp->Initialize();

	if(!initialized) {
		printf("Init failed!");
		return 0;
	}

	UIManager *uimgr = winApp->GetUIManager();
	PanelControl *panel = new PanelControl(CFrame(100, 100, 100, 50));
	panel->SetBackgroundColor(CColor(0, 255, 0, 1));
	uimgr->AddRootControl(panel);

	auto mouseCallback = std::bind(ButtonMouseCallback, std::placeholders::_1, std::placeholders::_2);

	ButtonControl *button = new ButtonControl(CFrame(5, 5, 50, 20));
	button->SetBackgroundColor(CColor(255, 0, 0, 1));
	button->AddMouseDownDelegate(mouseCallback);
	button->AddMouseUpDelegate(mouseCallback);
	button->SetZPosition(100);
	panel->AddSubcontrol(button);

	ButtonControl *button2 = new ButtonControl(CFrame(15, 15, 50, 20));
	button2->SetBackgroundColor(CColor(0, 0, 255, 1));
	button2->AddMouseDownDelegate(mouseCallback);
	button2->AddMouseUpDelegate(mouseCallback);
	panel->AddSubcontrol(button2);

	Logger::log(LogDebug, "Game Initialized");

	// Main message loop:
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(1));
	MSG msg;

	int desiredFPS = 60;
	int frameTime = 1000000000 / desiredFPS;
	SYSTEMTIME systemTime;

	//CTimer *timer = new CTimer(1000, FPSCallback, NULL, true);
	bool done = false;
	while (!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			GetMessage(&msg, NULL, 0, 0);
			DispatchMessage(&msg);
		}
		LARGE_INTEGER time1, time2;
		QueryPerformanceCounter(&time1);

		winApp->Update();
		winApp->Render();
		QueryPerformanceCounter(&time2);

		int dif = frameTime - (time2.QuadPart - time1.QuadPart);
		if (dif > 0) {
			Sleep(dif * 0.000001);
		}
		nFrames++;
	}
	return 0;
}