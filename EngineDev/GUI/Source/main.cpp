#include <time.h>
#include <Challenge/GameApplicationWindows.h>
#include <Challenge/Util/Timer.h>
#include <Challenge/Util/Logger.h>
#include <Challenge/Platform/Win32/CWindow.h>
#include "GUITesting.h"
using namespace challenge;

void FPSCallback(void *obj);
int nFrames = 0;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Size screenSize(1600, 1024);

	std::shared_ptr<GUITesting> app(new GUITesting());

	CWindow *window = new CWindow(hInstance, "", screenSize, app);
	if (!window->Initialize()) {
		throw "Failed to initialize window!";
	}

	window->SetWindowVisibility(WindowVisible);

	return window->StartMainLoop();
}