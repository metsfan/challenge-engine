#pragma once

#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>

namespace challenge 
{
	class GameApplicationWindows : public GameApplication
	{
	public:
		GameApplicationWindows(const Size &screenSize, HINSTANCE instance);
		virtual ~GameApplicationWindows(void);

		virtual bool Initialize();

		virtual void RunMainLoop(AppCallback updateCallback, AppCallback renderCallback);

		HWND GetWinHandle() { return mWinHandle; }

	private:
		HINSTANCE mInstance;
		HWND mWinHandle;
	};
};