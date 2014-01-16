#include <Challenge/Challenge.h>
#include <Challenge/Core/RunLoop.h>

namespace challenge
{
	RunLoop::RunLoop(int framerate, TRunLoopCallback callback) :
		mRunning(true)
	{
		mRunLoopThread = std::thread([framerate, callback, this] {
			int frameTime = 1000000 / framerate;

			int deltaMillis = 0;
			LARGE_INTEGER time1, time2, freq;
			QueryPerformanceCounter(&time2);
			QueryPerformanceFrequency(&freq);

			while (mRunning) {
				QueryPerformanceCounter(&time1);
				deltaMillis = ((time1.QuadPart - time2.QuadPart) * 1000) / freq.QuadPart;

				callback(deltaMillis);

				QueryPerformanceCounter(&time2);
				LONG64 time = ((time2.QuadPart - time1.QuadPart) * 1000000) / freq.QuadPart;

				int dif = frameTime - time;
				if (dif > 0) {
					std::this_thread::sleep_for(std::chrono::microseconds(dif));
				}

				time2 = time1;
			}
		});
	}

	RunLoop::~RunLoop()
	{
		mRunning = false;
		mRunLoopThread.join();
	}
}