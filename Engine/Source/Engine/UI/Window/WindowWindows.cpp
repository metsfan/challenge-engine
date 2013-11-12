#include <Engine/Challenge.h>
#include "WindowWindows.h"
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	Window<PlatformTypeWin32>::Window(HINSTANCE hInstance, std::string title, Size size, IWindowListener *listener) :
		BaseWindow(title, size, listener),
		mInstance(hInstance),
		mRunning(false)
	{
	}

	Window<PlatformTypeWin32>::~Window()
	{
	}

	bool Window<PlatformTypeWin32>::Initialize()
	{
		if (mInstance != NULL) {
			mWindowClass = "GameWindow";
			mRegisterClass = CreateRegisterClass(mInstance);

			const Size& size = this->GetSize();
			if (mRegisterClass != 0) {
				mWinHandle = CreateWindow(mWindowClass, this->GetTitle().c_str(), kDefaultWindowStyle, 0, 0, size.width, size.height, 
											NULL, NULL, mInstance, NULL);
				SetWindowLong(mWinHandle, GWL_USERDATA, (LONG)this); 

				RECT winSize, actualSize;
				GetWindowRect(mWinHandle, &winSize);
				GetClientRect(mWinHandle, &actualSize);

				int difX = winSize.right - actualSize.right;
				int difY = winSize.bottom - actualSize.bottom;
				MoveWindow(mWinHandle, 0, 0, size.width + difX, size.height + difY, TRUE);

				if (mWinHandle != NULL) {
					mDC = GetDC(mWinHandle);
				} else {
					int error = GetLastError();
					printf("Error: %d", error);
					return false;
				}
			} else {
				int error = GetLastError();
				printf("Error: %d", error);
				return false;
			}

			GameApplicationWindows *app = new GameApplicationWindows(size, mInstance, mWinHandle);
			if (!app->Initialize()) {
				return false;
			}

			this->WindowInitialized(app);

			return true;
		}

		return false;
	}

	int Window<PlatformTypeWin32>::StartMainLoop()
	{
		MSG msg;

		int desiredFPS = 60;
		int frameTime = 1000000 / desiredFPS;

		int deltaMillis = 0;
		LARGE_INTEGER time1, time2, freq;
		QueryPerformanceCounter(&time2);
		QueryPerformanceFrequency(&freq);

		int totalTime = 0;
		int frames = 0;

		mRunning = true;

		while (mRunning)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
				GetMessage(&msg, NULL, 0, 0);
				DispatchMessage(&msg);
			}
			else {
				QueryPerformanceCounter(&time1);
				deltaMillis = (time1.QuadPart - time2.QuadPart) * 0.000001;

				this->WindowUpdate(deltaMillis);

				this->WindowDraw();

				QueryPerformanceCounter(&time2);
				LONG64 time = ((time2.QuadPart - time1.QuadPart) * 1000000) / freq.QuadPart;

				int dif = frameTime - time;
				if (dif > 0) {
					std::this_thread::sleep_for(std::chrono::microseconds(dif));
				}

				time2 = time1;
			}
		}

		return 0;
	}

	void Window<PlatformTypeWin32>::SetSize(Size size)
	{
		BaseWindow::SetSize(size);

		SetWindowPos(mWinHandle, NULL, 0, 0, size.width, size.height, SWP_SHOWWINDOW);
	}

	void Window<PlatformTypeWin32>::SetWindowVisibility(WindowVisibility visibility)
	{
		BaseWindow::SetWindowVisibility(visibility);

		int cmdShow;
		switch(visibility) 
		{
		case WindowHidden:
			cmdShow = SW_HIDE;
			break;

		case WindowMinimized:
			cmdShow = SW_MINIMIZE;
			break;

		case WindowVisible:
		default:
			cmdShow = SW_SHOW;
		}

		ShowWindow(mWinHandle, cmdShow);
	}

	void Window<PlatformTypeWin32>::AttachToDevice(GraphicsDevice<RendererTypeDX11> *device)
	{
		device->SetWindowHandle(mWinHandle);
	}

	ATOM Window<PlatformTypeWin32>::CreateRegisterClass(HINSTANCE instance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= Window<PlatformTypeWin32>::WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= instance;
		wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		wcex.hIconSm		= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= mWindowClass;

		return RegisterClassEx(&wcex);
	}

	LRESULT CALLBACK Window<PlatformTypeWin32>::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		POINTS mousePoints = MAKEPOINTS(lParam);
		Point mousePos;
		mousePos.x = mousePoints.x;
		mousePos.y = mousePoints.y;

		int repeatCount = (lParam & 0xffff);

		Window<PlatformTypeWin32> *window = reinterpret_cast<Window<PlatformTypeWin32> *>(GetWindowLong(hWnd, GWL_USERDATA));

		if(window) {
			IWindowInputReader *inputReader = window->GetInputReader();

			if(inputReader) {
			switch (uMsg) {
				case WM_SYSKEYUP:
				case WM_KEYUP:
					inputReader->ProcessKeyboardEvent(KeyboardEventKeyUp, wParam);
					break;

				case WM_SYSKEYDOWN:
				case WM_KEYDOWN:
					if(repeatCount <= 1) {
						inputReader->ProcessKeyboardEvent(KeyboardEventKeyDown, wParam);
					}
					break;

				case WM_LBUTTONDOWN:
					inputReader->ProcessMouseEvent(MouseEventMouseDown, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONDOWN:
					inputReader->ProcessMouseEvent(MouseEventMouseDown, MouseButtonRight, mousePos);
					break;

				case WM_MBUTTONDOWN:
					inputReader->ProcessMouseEvent(MouseEventMouseDown, MouseButtonMiddle, mousePos);
					break;

				case WM_LBUTTONUP:
					inputReader->ProcessMouseEvent(MouseEventMouseUp, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONUP:
					inputReader->ProcessMouseEvent(MouseEventMouseUp, MouseButtonRight, mousePos);
					break;

				case WM_MBUTTONUP:
					inputReader->ProcessMouseEvent(MouseEventMouseUp, MouseButtonMiddle, mousePos);
					break;

				case WM_LBUTTONDBLCLK:
					inputReader->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONDBLCLK:
					inputReader->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonRight, mousePos);
					break;

				case WM_MBUTTONDBLCLK:
					inputReader->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonMiddle, mousePos);
					break;

				case WM_MOUSEMOVE:
					{
						int button = MouseButtonLeft;
						if(wParam & MK_RBUTTON) {
							button = MouseButtonRight;
						} else if(wParam & MK_MBUTTON) {
							button = MouseButtonMiddle;
						}
						inputReader->ProcessMouseEvent(MouseEventMouseMove, button, mousePos);
					}
					
					break;

				case WM_MOUSEWHEEL:
					{
						int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
						inputReader->ProcessMouseWheelEvent(MouseEventMouseWheelMove, wheelDelta);
					}
					break;
				}
			}
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
};