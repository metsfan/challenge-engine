#include <Engine/Challenge.h>
#include "WindowWindows.h"
#include <Engine/Renderer/Device/GraphicsDeviceDX11.h>

namespace challenge
{
	Window<PlatformTypeWindows>::Window(HINSTANCE hInstance, std::string title, Size size) :
		BaseWindow(title, size),
		mInstance(hInstance)
	{
	}

	Window<PlatformTypeWindows>::~Window()
	{
	}

	bool Window<PlatformTypeWindows>::Initialize()
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
					return true;
				} else {
					int error = GetLastError();
					printf("Error: %d", error);
				}
			} else {
				int error = GetLastError();
				printf("Error: %d", error);
			}
		}

		return false;
	}

	void Window<PlatformTypeWindows>::SetSize(Size size)
	{
		BaseWindow::SetSize(size);

		SetWindowPos(mWinHandle, NULL, 0, 0, size.width, size.height, SWP_SHOWWINDOW);
	}

	void Window<PlatformTypeWindows>::SetWindowVisibility(WindowVisibility visibility)
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

	void Window<PlatformTypeWindows>::AttachToDevice(GraphicsDevice<RendererTypeDX11> *device)
	{
		device->SetWindowHandle(mWinHandle);
	}

	ATOM Window<PlatformTypeWindows>::CreateRegisterClass(HINSTANCE instance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= Window<PlatformTypeWindows>::WndProc;
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

	LRESULT CALLBACK Window<PlatformTypeWindows>::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		POINTS mousePoints = MAKEPOINTS(lParam);
		Point mousePos;
		mousePos.x = mousePoints.x;
		mousePos.y = mousePoints.y;

		int repeatCount = (lParam & 0xffff);

		Window<PlatformTypeWindows> *window = reinterpret_cast<Window<PlatformTypeWindows> *>(GetWindowLong(hWnd, GWL_USERDATA));

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

				case WM_LBUTTONUP:
					inputReader->ProcessMouseEvent(MouseEventMouseUp, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONUP:
					inputReader->ProcessMouseEvent(MouseEventMouseUp, MouseButtonRight, mousePos);
					break;

				case WM_LBUTTONDBLCLK:
					inputReader->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonLeft, mousePos);
					break;

				case WM_RBUTTONDBLCLK:
					inputReader->ProcessMouseEvent(MouseEventMouseDblClick, MouseButtonRight, mousePos);
					break;

				case WM_MOUSEMOVE:
					inputReader->ProcessMouseEvent(MouseEventMouseMove, 0, mousePos);
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