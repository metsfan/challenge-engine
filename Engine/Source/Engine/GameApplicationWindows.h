#pragma once

#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>

namespace challenge 
{
	

	class GameApplicationWindows : public GameApplication
	{
	public:
		GameApplicationWindows(HINSTANCE instance);
		virtual ~GameApplicationWindows(void);

		virtual bool Initialize();

		virtual void RunMainLoop(AppCallback updateCallback, AppCallback renderCallback);

	private:
		HINSTANCE mInstance;
	};
};