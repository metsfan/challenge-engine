#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>

namespace challenge
{
	static const int kDefaultWindowStyle = WS_OVERLAPPEDWINDOW;
	static const int kWindowsFullscreenStyle = WS_EX_TOPMOST | WS_POPUP;

	class CWindow
	{
	public:
		CWindow(HINSTANCE hInstance, std::string title, Size size, std::shared_ptr<IApplicationListener> listener);
		~CWindow();

		bool Initialize();

		void SetTitle(std::string title);
		const std::string& GetTitle() const { return mTitle; }

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
		Size mSize;
		std::string mTitle;
		std::shared_ptr<IApplicationListener> mListener;

		GameApplicationWindows *mApplication;

		void AttachToDevice(GraphicsDevice<RendererTypeDX11> *device);

		ATOM CreateRegisterClass(HINSTANCE instance);
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		static void ProcessKeyEvent(GameApplication *application, KeyboardEventType evt, WPARAM wParam, LPARAM lParam);
		static WCHAR TranslateVirtualKeyCode(WPARAM wParam, LPARAM lParam);
	};

	static int CreateGameWindow(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPTSTR    lpCmdLine,
		_In_ int       nCmdShow);
};