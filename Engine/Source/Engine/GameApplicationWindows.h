#pragma once

#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>

namespace challenge 
{
	class GameApplicationWindows : public GameApplication
	{
	public:
		GameApplicationWindows(std::shared_ptr<Window> window, 
								std::shared_ptr<IApplicationListener> listener,
								HINSTANCE instance, 
								HWND winHandle);
		virtual ~GameApplicationWindows(void);

		virtual bool Initialize();

		HWND GetWinHandle() { return mWinHandle; }

	private:
		HINSTANCE mInstance;
		HWND mWinHandle;
	};
};