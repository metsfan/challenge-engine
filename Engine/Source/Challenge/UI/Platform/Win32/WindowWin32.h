#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Window.h>

namespace challenge
{
	class WindowWin32 : public Window
	{
	public:
		WindowWin32(Size size, HWND winHandle);
		~WindowWin32();

		void ShowNativeFileDialog(FILE_DIALOG_DESC *desc);

	private:
		HWND mWinHandle;
	};
};