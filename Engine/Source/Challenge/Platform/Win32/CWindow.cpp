#include <Challenge/Challenge.h>
#include <Challenge/Platform/Win32/CWindow.h>
#include <Challenge/Renderer/Device/GraphicsDeviceDX11.h>
#include <Challenge/Input/InputManager.h>
#include <Challenge/UI/Platform/Win32/WindowWin32.h>

namespace challenge
{
	CWindow::CWindow(HINSTANCE hInstance, std::string title, Size size, std::shared_ptr<IApplicationListener> listener) :
		mInstance(hInstance),
		mRunning(false),
		mSize(size),
		mTitle(title),
		mListener(listener)
	{
	}

	CWindow::~CWindow()
	{
	}

	bool CWindow::Initialize()
	{

		if (mInstance != NULL) {
			CoInitialize(NULL);

			mWindowClass = "GameWindow";
			mRegisterClass = CreateRegisterClass(mInstance);
			if (mRegisterClass != 0) {
				mWinHandle = CreateWindow(mWindowClass, mTitle.c_str(), kDefaultWindowStyle, 0, 0, mSize.width, mSize.height,
											NULL, NULL, mInstance, NULL);
				SetWindowLong(mWinHandle, GWL_USERDATA, (LONG)this); 

				RECT winSize, actualSize;
				GetWindowRect(mWinHandle, &winSize);
				GetClientRect(mWinHandle, &actualSize);

				int difX = winSize.right - actualSize.right;
				int difY = winSize.bottom - actualSize.bottom;
				MoveWindow(mWinHandle, 0, 0, mSize.width + difX, mSize.height + difY, TRUE);

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

			std::shared_ptr<Window> window(new Window(mSize));

			mApplication = new GameApplicationWindows(window, mListener, mInstance, mWinHandle);
			if (!mApplication->Initialize()) {
				return false;
			}

			return true;
		}

		return false;
	}

	void CWindow::SetTitle(std::string title)
	{

	}

	int CWindow::StartMainLoop()
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
				deltaMillis = ((time1.QuadPart - time2.QuadPart) * 1000) / freq.QuadPart;

				mApplication->Update(deltaMillis);

				mApplication->Render();

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

	void CWindow::SetSize(Size size)
	{
		mApplication->GetWindow()->SetSize(size);

		SetWindowPos(mWinHandle, NULL, 0, 0, size.width, size.height, SWP_SHOWWINDOW);
	}

	void CWindow::SetWindowVisibility(WindowVisibility visibility)
	{
		mApplication->GetWindow()->SetWindowVisibility(visibility);

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

	void CWindow::AttachToDevice(GraphicsDevice<RendererTypeDX11> *device)
	{
		device->SetWindowHandle(mWinHandle);
	}

	ATOM CWindow::CreateRegisterClass(HINSTANCE instance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= CWindow::WndProc;
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

	LRESULT CALLBACK CWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		POINTS mousePoints = MAKEPOINTS(lParam);
		Point mousePos;
		mousePos.x = mousePoints.x;
		mousePos.y = mousePoints.y;

		int repeatCount = (lParam & 0xffff);

		CWindow *window = reinterpret_cast<CWindow *>(GetWindowLong(hWnd, GWL_USERDATA));
		if (window) {
			auto application = window->mApplication;

			if (application) {
				switch (uMsg) {
				case WM_SYSKEYUP:
				case WM_KEYUP:
					ProcessKeyEvent(application, KeyboardEventKeyUp, wParam, lParam);
					break;

				case WM_SYSKEYDOWN:
				case WM_KEYDOWN:
					if (repeatCount <= 1) {					
						ProcessKeyEvent(application, KeyboardEventKeyDown, wParam, lParam);
					}
					break;	

				case WM_LBUTTONDOWN:
					application->ProcessMouseEvent(MouseEventMouseDown, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONDOWN:
					application->ProcessMouseEvent(MouseEventMouseDown, MouseButtonRight, mousePos);
					break;

				case WM_MBUTTONDOWN:
					application->ProcessMouseEvent(MouseEventMouseDown, MouseButtonMiddle, mousePos);
					break;

				case WM_LBUTTONUP:
					application->ProcessMouseEvent(MouseEventMouseUp, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONUP:
					application->ProcessMouseEvent(MouseEventMouseUp, MouseButtonRight, mousePos);
					break;

				case WM_MBUTTONUP:
					application->ProcessMouseEvent(MouseEventMouseUp, MouseButtonMiddle, mousePos);
					break;

				case WM_LBUTTONDBLCLK:
					application->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONDBLCLK:
					application->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonRight, mousePos);
					break;

				case WM_MBUTTONDBLCLK:
					application->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonMiddle, mousePos);
					break;

				case WM_MOUSEMOVE:
					{
						int button = MouseButtonLeft;
						if(wParam & MK_RBUTTON) {
							button = MouseButtonRight;
						} else if(wParam & MK_MBUTTON) {
							button = MouseButtonMiddle;
						}
						application->ProcessMouseEvent(MouseEventMouseMove, button, mousePos);
					}
					
					break;

				case WM_MOUSEWHEEL:
					{
						int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
						application->ProcessMouseWheelEvent(MouseEventMouseWheelMove, wheelDelta);
					}
					break;
				}
			}
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void CWindow::ProcessKeyEvent(GameApplication *application, KeyboardEventType evt, WPARAM wParam, LPARAM lParam)
	{
		switch (wParam)
		{
		case VK_SHIFT:
		case VK_LSHIFT:
		case VK_RSHIFT:
			application->ProcessKeyboardEvent(evt, SpecialKeyShift);
			break;

		case VK_CONTROL:
		case VK_LCONTROL:
		case VK_RCONTROL:
			application->ProcessKeyboardEvent(evt, SpecialKeyCtrl);
			break;

		case LVKF_ALT:
			application->ProcessKeyboardEvent(evt, SpecialKeyAlt);
			break;

		case VK_DELETE:
			application->ProcessKeyboardEvent(evt, SpecialKeyDelete);
			break;

		case VK_LEFT:
			application->ProcessKeyboardEvent(evt, SpecialKeyLeft);
			break;

		case VK_RIGHT:
			application->ProcessKeyboardEvent(evt, SpecialKeyRight);
			break;

		case VK_UP:
			application->ProcessKeyboardEvent(evt, SpecialKeyUp);
			break;

		case VK_DOWN:
			application->ProcessKeyboardEvent(evt, SpecialKeyDown);
			break;

		case VK_TAB:
			application->ProcessKeyboardEvent(evt, SpecialKeyTab);
			break;

		case VK_SPACE:
			application->ProcessKeyboardEvent(evt, TranslateVirtualKeyCode(wParam, lParam, true));

		case VK_RETURN:
			application->ProcessKeyboardEvent(evt, SpecialKeyEnter);

		default:
			application->ProcessKeyboardEvent(evt, 
				TranslateVirtualKeyCode(wParam, lParam, true), 
				TranslateVirtualKeyCode(wParam, lParam, false));
		}
	}

	WCHAR CWindow::TranslateVirtualKeyCode(WPARAM wParam, LPARAM lParam, bool realKeys)
	{
		BYTE kbstate[256];
		GetKeyboardState(kbstate);
		if (realKeys) {
			kbstate[VK_SHIFT] = 0;
			kbstate[VK_CONTROL] = 0;
		}

		WCHAR outChar;
		ToUnicode(wParam, lParam, kbstate, &outChar, 1, 0);

		return outChar;
	}
};