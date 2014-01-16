#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	typedef std::function<void(int deltaMillis)> TRunLoopCallback;

	class RunLoop
	{
	public:
		RunLoop(int framerate, TRunLoopCallback callback);
		~RunLoop();

	private:
		std::thread mRunLoopThread;
		bool mRunning;
	};
};