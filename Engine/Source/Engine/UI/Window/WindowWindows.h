#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/UI/Window.h>

namespace challenge
{
	static const int kDefaultWindowStyle = WS_OVERLAPPEDWINDOW;
	static const int kWindowsFullscreenStyle = WS_EX_TOPMOST | WS_POPUP;

	template<>
	class Window<PlatformTypeWin32> : public BaseWindow
	{
	public:
		Window(HINSTANCE hInstance, std::string title, Size size, IWindowListener *listener);
		~Window();

		bool Initialize();

		void SetWindowVisibility(WindowVisibility visibility);

		void SetSize(Size size);

		int StartMainLoop();

		HWND GetWinHandle() { return mWinHandle; }

	private:
		HWND mWinHandle;
		HDC mDC;
		HINSTANCE mInstance;
		LPCSTR mWindowClass;
		ATOM mRegisterClass;
		BOOL mRunning;

		void AttachToDevice(GraphicsDevice<RendererTypeDX11> *device);

		ATOM CreateRegisterClass(HINSTANCE instance);
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	};

	typedef Window<PlatformTypeWin32> WindowWin32;
};