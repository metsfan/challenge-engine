#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Window.h>

namespace challenge
{
	class WindowWin32 : public Window
	{
	public:
		WindowWin32(Size size, HWND winHandle);
		~WindowWin32();

	private:
		HWND mWinHandle;
	};
};