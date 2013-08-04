#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Window.h>

namespace challenge
{
	static const int kDefaultWindowStyle = WS_OVERLAPPEDWINDOW;
	static const int kWindowsFullscreenStyle = WS_EX_TOPMOST | WS_POPUP;

	template<>
	class Window<PlatformTypeWindows> : public BaseWindow
	{
	public:
		Window(HINSTANCE hInstance, std::string title, Size size);
		~Window();

		bool Initialize();

		void SetWindowVisibility(WindowVisibility visibility);

		void SetSize(Size size);

		void AttachToDevice(GraphicsDevice<RendererTypeDX11> *device);

	private:
		HWND mWinHandle;
		HDC mDC;
		HINSTANCE mInstance;
		LPCSTR mWindowClass;
		ATOM mRegisterClass;

		ATOM CreateRegisterClass(HINSTANCE instance);
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	};
};